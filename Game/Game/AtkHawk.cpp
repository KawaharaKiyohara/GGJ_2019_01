#include "stdafx.h"
#include "AtkHawk.h"
#include "Bird.h"
#include "HawkGene.h"
#include "Hawk.h"
AtkHawk::AtkHawk()
{
	m_bird = FindGO<Bird>(GameObjectNames::BIRD);
	m_Hawk = FindGO<Hawk>(GameObjectNames::HAWK, false);
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

	m_oldbirdpos = m_Hawk->m_PlayerPos;

	m_movespeed = m_oldbirdpos - m_HawkPos;
	m_muki = m_movespeed;
	m_movespeed.Normalize();
	
	m_movespeed *= 30;

	m_muki.y = 0.0f;
 	m_muki.Normalize();
	m_rot.SetRotation({ 0.0f,0.0f,1.0 }, m_muki);
	m_skinModelRender->SetRotation(m_rot);
	return true;

}
void AtkHawk::Update()
{
	

	switch (m_state)
	{
	case AtkHawk::enState_Descent:
		
			m_HawkPos += m_movespeed ;
		
		if (m_HawkPos.y < m_oldbirdpos.y) {
			m_state = enState_Atk;
		}
		break;
	case AtkHawk::enState_Atk:
		m_bird->Death();
		DeleteGO(m_Hawk);
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