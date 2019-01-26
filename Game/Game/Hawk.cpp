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
	//�V���h�E�L���X�^�[�ƃV���h�E���V�[�o�[�̃t���O�𗧂Ă�B
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	m_skinModelRender->SetDrawShadowOnly();
	m_PlayerPos = m_bird->GetPosition();
	m_PlayerPos.y += 50.0f;
	
	m_skinModelRender->SetPosition(m_PlayerPos);

	
	return true;
}
void Hawk::Update()
{
	kierucount++;
	
	if (kierucount == 50) {
		m_AtkHawk = NewGO<AtkHawk>(0);
	}

	
}