#include "stdafx.h"
#include "Hawk.h"
#include "Bird.h"

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
	m_skinModelRender->Init(CmoFilePaths::HAWK);
	//シャドウキャスターとシャドウレシーバーのフラグを立てる。
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	
	m_PlayerPos = m_bird->GetPosition();
	m_PlayerPos.y += 50.0f;
	
	m_skinModelRender->SetPosition(m_PlayerPos);
	return true;
}
void Hawk::Update()
{
}