#include "stdafx.h"
#include "Bird.h"


Bird::Bird()
{
}


Bird::~Bird()
{
	DeleteGO(m_skinModelRender);
}
bool Bird::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(CmoFilePaths::BIRD);
	//�V���h�E�L���X�^�[�ƃV���h�E���V�[�o�[�̃t���O�𗧂Ă�B
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	return true;
}
void Bird::Update()
{
}