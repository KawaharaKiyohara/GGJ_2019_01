#pragma once
#include "tkEngine/camera/tkSpringCamera.h"
class Bird;
class GameCamera: public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	//�J�����̍��W���擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//�J�����̒����_���擾
	CVector3 GetTartget() const
	{
		return m_target;
	}
	//�J�����̍��W����ђ����_�̌v�Z
	void TPS();
private:
	CVector3 m_topos = CVector3::Zero;
	CVector3 m_playerposition;
	float m_degreexz = 0.0f;
	float m_degreey = 0.0f;
	float m_sdegreexz = 0.0f;
	float m_sdegreey = 0.0f;
	const float m_r = 140.0f;
	float m_radianx;
	float m_radiany;
	CVector3 m_target=CVector3::Zero;
	CVector3 m_position = CVector3::Zero;

	Bird* m_bird = nullptr;
	CSpringCamera m_springcamera;
};

