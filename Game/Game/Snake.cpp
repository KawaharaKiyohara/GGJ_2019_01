#include "stdafx.h"
#include "Snake.h"
#include "Timer.h"

Snake::Snake()
{
}


Snake::~Snake()
{
	DeleteGO(m_skinModelRender);
}

bool Snake::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(CmoFilePaths::SNAKE);
	m_skinModelRender->SetPosition(m_pos);
	m_skinModelRender->SetRotation(rotation);
	//�V���h�E�L���X�^�[�ƃV���h�E���V�[�o�[�̃t���O�𗧂Ă�B
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	m_charaCon.Init(
		20.0,			//���a�B 
		100.0f,			//�����B
		m_pos		//�����ʒu�B
	);
	//pos = m_pos;
	bird = FindGO<Bird>(GameObjectNames::BIRD);
	//timer = FindGO<Timer>(0);

	//timer = NewGO<Timer>(0);
	return true;
}
void Snake::Move() {
	//�����X�^�[���v���C���[�ɋ߂Â�
	kyori = bird->GetPosition() - m_pos;
	kyori.Normalize();
	kyori.y = 0.0f;
	kyori = kyori * 5;
	//pos += kyori2;0
	s_Speed += kyori;
	
	if (kyori.Length() < 2000.0f) {
		
		m_pos = m_charaCon.Execute(s_Speed,GameTime().GetFrameDeltaTime());
	}
	else if (kyori.Length() > 20.0f) {

	}
	m_skinModelRender->SetPosition(m_pos);
}
void Snake::Rotation() {

	if (s_Speed.x<0
		&& s_Speed.x>s_Speed.z) {
		rotation.SetRotationDeg(CVector3::AxisY, 180.0f);
	}
	if (s_Speed.x > 0
		&& s_Speed.x > s_Speed.z) {
		rotation.SetRotationDeg(CVector3::AxisY, 90.0f);
	}
	if (s_Speed.z < 0
		&& s_Speed.x < s_Speed.z) {
		rotation.SetRotationDeg(CVector3::AxisY, -90.0f);
	}
	if (s_Speed.z > 0
		&& s_Speed.x < s_Speed.z) {
		rotation.SetRotationDeg(CVector3::AxisY, 0.0f);
	}

	m_skinModelRender->SetRotation(rotation);
}
void Snake::Update()
{
	Move();
	Rotation();
}