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
	syokipos = m_pos;
	bird = FindGO<Bird>(GameObjectNames::BIRD);
	//timer = FindGO<Timer>(0);

	//timer = NewGO<Timer>(0);
	return true;
}
void Snake::Move() {
	//�����X�^�[���v���C���[�ɋ߂Â�
	kyori = bird->GetPosition() - m_pos;
	float len = kyori.Length();
	kyori.Normalize();
	kyori.y = 0.0f;
	kyori = kyori * 5;
	//pos += kyori2;
	s_Speed = kyori * 35;
	
	kyori2 = syokipos - m_pos;
	float len2 = kyori2.Length();

	if (len2 > 600.0f) {
		m_return = true;
	}
	if (m_return) {
		kyori2.Normalize();
		kyori2.y = 0.0f;
		kyori2 = kyori2 * 5;
		s_Speed = kyori2 * 80;
		m_pos = m_charaCon.Execute(s_Speed, GameTime().GetFrameDeltaTime());
		if (len2 <= 100.0f) {
			m_return = false;
			m_heit = false;
		}
	}
	else if (len < 700.0f) {
		m_heit = true;
		m_pos = m_charaCon.Execute(s_Speed,GameTime().GetFrameDeltaTime());
	}

	m_skinModelRender->SetPosition(m_pos);
}
void Snake::Rotation() {

	if (m_heit) {
		rotation.SetRotation(CVector3::AxisY, atan2(s_Speed.x, s_Speed.z));
	}
	m_skinModelRender->SetRotation(rotation);
}
void Snake::Update()
{
	Move();
	Rotation();
}