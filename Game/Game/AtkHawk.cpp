#include "stdafx.h"
#include "AtkHawk.h"
#include "Bird.h"
#include "HawkGene.h"

AtkHawk::AtkHawk()
{
	m_bird = FindGO<Bird>(GameObjectNames::BIRD);
}


AtkHawk::~AtkHawk()
{
	DeleteGO(m_skinModelRender);
}

bool AtkHawk::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(CmoFilePaths::HAWK);
	
	m_PlayerPos = m_bird->GetPosition();

	m_HawkPos = m_PlayerPos + (MainCamera().GetRight() * 500);
	m_HawkPos.y += 350.0f;

	m_skinModelRender->SetPosition(m_HawkPos);

	m_oldbirdpos = m_bird->GetPosition();

	m_movespeed = m_oldbirdpos - m_HawkPos;
	m_movespeed.Normalize();
	m_movespeed *= 11;

	return true;

}
void AtkHawk::Update()
{
	

	switch (m_state)
	{
	case AtkHawk::enState_Descent:
		
			m_HawkPos += m_movespeed;
		
		if (m_HawkPos.y < m_oldbirdpos.y) {
			m_state = enState_Atk;
		}
		break;
	case AtkHawk::enState_Atk:
		m_bird->Death();
		m_state = enState_return;
		break;
	case AtkHawk::enState_return:
		if (m_skinModelRender->GetShadowCaster() == false) {
			m_skinModelRender->SetShadowCasterFlag(true);
			m_skinModelRender->SetShadowReceiverFlag(true);
		}
		m_HawkPos.x += m_movespeed.x;
		m_HawkPos.y -= m_movespeed.y;
		m_HawkPos.z += m_movespeed.z;
		if (m_HawkPos.y > 350.0f) {
			DeleteGO(this);
		}
		break;
	default:
		break;
	}
	
	
	
	m_skinModelRender->SetPosition(m_HawkPos);
	
}