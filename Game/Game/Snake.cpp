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
	//シャドウキャスターとシャドウレシーバーのフラグを立てる。
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	m_skinModelRender->SetScale({ 0.8f, 0.8f, 0.5f });
	m_charaCon.Init(
		20.0,			//半径。 
		100.0f,			//高さ。
		m_pos		//初期位置。
	);
	syokipos = m_pos;
	bird = FindGO<Bird>(GameObjectNames::BIRD);
	//timer = FindGO<Timer>(0);

	//timer = NewGO<Timer>(0);
	return true;
}
void Snake::Move() {
	//モンスターがプレイヤーに近づく
	kyori = bird->GetPosition() - m_pos;
	len = kyori.Length();
	kyori.Normalize();
	kyori.y = 0.0f;
	kyori = kyori * 5;
	//pos += kyori2;
	s_Speed = kyori * 35;
	
	kyori2 = syokipos - m_pos;
	float len2 = kyori2.Length();

	if (!m_attack) {
		s_Speed = CVector3::Zero;
		m_timer += 30.0f*GameTime().GetFrameDeltaTime();
		if (m_timer >= m_cooltime) {
			m_timer = 0.0f;
			m_attack = true;
		}
	}
	else {
		m_rot = s_Speed;
	}
	if (len2 > 700.0f) {
		m_return = true;
	}
	if (m_return) {
		kyori2.Normalize();
		kyori2.y = 0.0f;
		kyori2 = kyori2 * 5;
		s_Speed = kyori2 * 80;
		m_pos = m_charaCon.Execute(s_Speed, GameTime().GetFrameDeltaTime());
		m_rot = s_Speed;
		if (len2 <= 100.0f) {
			m_return = false;
			m_heit = false;
		}
	}
	else if (len <= 700.0f) {
		m_heit = true;
		
		if (frg_attck1 == false
			&&len <= 200.0f) {
			s_Speed *= 4.0f;
			if (len <=60.0f) {
				s_Speed =s_Speed * 0.0f;
				bird->Damage();
				frg_attck1 = true;
				m_attack = false;
			}
		}
		if (len <=300) {
			frg_attck1 = false;
		}
	
		m_pos = m_charaCon.Execute(s_Speed, GameTime().GetFrameDeltaTime());
	}

	m_skinModelRender->SetPosition(m_pos);
}

void Snake::Attack() {

	
}
void Snake::Rotation() {

	if (m_heit
		//&&frg_attck1 == true
		) {
		rotation.SetRotation(CVector3::AxisY, atan2(m_rot.x, m_rot.z));
	}
	m_skinModelRender->SetRotation(rotation);
}
void Snake::Update()
{
	Move();
	
	Rotation();
}