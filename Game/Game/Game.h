#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
private:
	/// <summary>
	/// �|�X�g�G�t�F�N�g���������B
	/// </summary>
	void InitPostEffects();
	/// <summary>
	/// �f�B���N�V�������C�g���������B
	/// </summary>
	void InitDirectionLight();
	/// <summary>
	/// ����������B
	/// </summary>
	void InitSky();
	/// <summary>
	/// �����������B
	/// </summary>
	void InitBird();
	/// <summary>
	/// �W���}�[�������e�X�g�p�ɐ������Ƃ����B
	/// </summary>
	void InitTestJammers();
	/// <summary>
	/// �}�b�v���\�z����B
	/// </summary>
	void InitMap();

    /// �Q�[���J������������
    /// </summary>
	void InitGameCamera();
	/// <summary>
	/// �Q�[���J�n�J�b�g���o���쐬�B
	/// </summary>
	void InitGameStartCut();
private:
	/// <summary>
	/// �Q�[���X�e�b�v�B
	/// </summary>
	enum EnStep {
		enStep_StartCut,		//�J�n�J�b�g
		enStep_InGameGround,	//�n�ʂɂ���Ƃ��̃C���Q�[���B
		enStep_FlyCut,			//��s�J�b�g
		enStep_InGameSky,		//��ɂ���Ƃ��̃C���Q�[���B
		enStep_GameClearCut,	//�Q�[���N���A�J�b�g�B
	};
	EnStep m_step = enStep_StartCut;	//�Q�[���X�e�b�v�B
};

