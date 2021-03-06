#pragma once
#include "Bird.h"
#include "tkEngine/character/tkCharacterController.h"
#include "Timer.h"
class Game;
class Timer;
class Snake : public IGameObject
{
public:
	Snake();
	~Snake();
	bool Start() override;
	void Update() override;
	void Move();
	void Attack();
	void Rotation();
	
	CVector3 m_pos = CVector3::Zero;
	CVector3 syokipos = CVector3::Zero;
	CVector3 kyori2 = CVector3::Zero;
	CVector3 s_Speed = CVector3::Zero;
	CVector3 kyori = CVector3::Zero;
	CVector3 m_rot;
	CQuaternion rotation = CQuaternion::Identity;  //回転。
	CCharacterController m_charaCon;		         //キャラクターコントローラー。
	bool m_return = false;
	bool m_heit = false;
	bool m_chase = false;
	bool frg_attck1 = false;
	bool frg_attck2 = false;
	bool frg_attck3 = false;
	float m_timer = 0.0f;
	float m_cooltime = 50.0f;
	float len = 0.0f;
	bool m_attack = true;
	Bird* bird = nullptr;
	Timer* timer = nullptr;
	Game* m_game = nullptr;


};

