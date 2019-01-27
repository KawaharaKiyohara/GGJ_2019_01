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
	float len = kyori.LengthSq();
	kyori.Normalize();
	kyori.y = 0.0f;
	kyori = kyori * 5;
	//pos += kyori2;0
	s_Speed = kyori * 40;
	
	kyori2 = syokipos - m_pos;
	float len2 = kyori2.LengthSq();


	if (len < 500.0f * 500.0f) {
		
		m_pos = m_charaCon.Execute(s_Speed,GameTime().GetFrameDeltaTime());
	}
	else if (len2 > 400.0f * 400.0f) {
		kyori2.Normalize();
		kyori2.y = 0.0f;
		kyori2 = kyori2 * 5;
		s_Speed = kyori2 * 800;
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