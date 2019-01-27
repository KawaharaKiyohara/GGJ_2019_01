#include "stdafx.h"
#include "Hawk.h"
#include "Bird.h"
#include "AtkHawk.h"
Hawk::Hawk()
{
	m_bird = FindGO<Bird>(GameObjectNames::BIRD);
}


Hawk::~Hawk()
{
	DeleteGO(m_skinModelRender);
}

bool Hawk::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(CmoFilePaths::HAWKSHADOW);
	//シャドウキャスターとシャドウレシーバーのフラグを立てる。
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	m_skinModelRender->SetDrawShadowOnly();
	
	
	return true;
}
void Hawk::Update()
{
	kierucount++;
	if (kierucount < 30) {
		m_PlayerPos = m_bird->GetPosition();
		m_PlayerPos.y += 50.0f;

		m_skinModelRender->SetPosition(m_PlayerPos);

		m_HawkPos = m_PlayerPos + (MainCamera().GetRight() * 500);

		m_muki = m_PlayerPos - m_HawkPos;
		m_muki.y = 0.0f;
		m_muki.Normalize();
		m_rot.SetRotation({ 0.0f,0.0f,1.0 }, m_muki);
		m_skinModelRender->SetRotation(m_rot);
	}
	if (kierucount == 50) {
		m_AtkHawk = NewGO<AtkHawk>(0);
	}

	
}