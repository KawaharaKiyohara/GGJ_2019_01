#include "stdafx.h"
#include "AtkHawk.h"


AtkHawk::AtkHawk()
{
}


AtkHawk::~AtkHawk()
{
	DeleteGO(m_skinModelRender);
}

bool AtkHawk::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(CmoFilePaths::HAWK);
	//シャドウキャスターとシャドウレシーバーのフラグを立てる。
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);

	m_startpos = { -400.0f,350.0f,0.0f };

	m_skinModelRender->SetPosition(m_startpos);
	return true;
}
void AtkHawk::Update()
{
}