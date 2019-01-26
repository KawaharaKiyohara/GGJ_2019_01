#pragma once

#include "tkEngine/camera/tkSpringCamera.h"

/// <summary>
/// �Q�[���X�^�[�g�J�b�g
/// </summary>
class GameStartCut : public IGameObject
{
public:
	GameStartCut();
	~GameStartCut();
	void Update() override;
	bool Start() override;
private:
	/// <summary>
	/// ���s�X�e�b�v�B
	/// </summary>
	enum EnStep {
		enStep_AllView,		//�S�̂���Ւ��B
		enStep_ZoomIn,		//�X�^�[�g�n�_�ɃY�[���C���B
	};
	CVector3 m_startPosition = CVector3::Zero;	//�J�n�n�_�B
	CSpringCamera m_springCamera;	//�΂˃J�����B
	float m_timer = 0.0f;			//�^�C�}�[(�P�ʁF�b)
	EnStep m_step = enStep_AllView;	//�S�̂���Ւ��B
};

