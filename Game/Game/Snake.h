#pragma once
#include "Bird.h"
#include "tkEngine/character/tkCharacterController.h"
#include "Timer.h"
class Timer;
class Snake : public IGameObject
{
public:
	Snake();
	~Snake();
	bool Start() override;
	void Update() override;
	void Move();
	void Rotation();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;

	
	CVector3 m_pos = CVector3::Zero;
	CVector3 syokipos = CVector3::Zero;
	CVector3 kyori2 = CVector3::Zero;
	CVector3 s_Speed = CVector3::Zero;
	CVector3 kyori = CVector3::Zero;
	CQuaternion rotation = CQuaternion::Identity;  //��]�B
	CCharacterController m_charaCon;		         //�L�����N�^�[�R���g���[���[�B
	bool m_return = false;
	bool m_heit = false;
	bool m_chase = false;
	Bird* bird = nullptr;
	Timer* timer = nullptr;



};

