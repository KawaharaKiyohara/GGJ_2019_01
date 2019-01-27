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
		enStep_StageNoIn,	//�X�e�[�W�ԍ�����B
		enStep_StageNoWait,
		enStep_StageNoOut,	//�X�e�[�W�ԍ��ޏ�B
		enStep_AllView,		//�S�̂���Ւ��B
		enStep_ZoomIn_0,	//�X�^�[�g�n�_�ɃY�[���C���B
		enStep_ZoomIn_1,	//�X�^�[�g�n�_�ɃY�[���C���B
	};
	CVector3 m_startPosition = CVector3::Zero;	//�J�n�n�_�B
	CSpringCamera m_springCamera;	//�΂˃J�����B
	float m_timer = 0.0f;			//�^�C�}�[(�P�ʁF�b)
	EnStep m_step = enStep_AllView;	//�S�̂���Ւ��B
	prefab::CSoundSource* m_bgm = nullptr;	//BGM
	CVector2 m_stageFontPosition = { -1000.0f, 200.0f };
	prefab::CFontRender* m_stageFontRender = nullptr;
	std::unique_ptr<DirectX::SpriteFont > m_stageNoFont;
};

