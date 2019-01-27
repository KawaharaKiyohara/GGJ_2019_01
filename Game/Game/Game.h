#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class Fade;
class Bird;

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
	/// �W���}�[�����𐶐����Ƃ����B
	/// </summary>
	void InitJammers();
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

	/// <summary>
	/// �Q�[���N���A�J�b�g���o���쐬�B
	/// </summary>
	void InitGameClearCut();

	/// �a��������
    /// </summary>
	void InitFeed();
private:
	/// <summary>
	/// �Q�[���X�e�b�v�B
	/// </summary>
	enum EnStep {
		enStep_WaitFadeIn,			//�t�F�[�h�C�����B
		enStep_StartCut,			//�J�n�J�b�g
		enStep_InGameGround,		//�n�ʂɂ���Ƃ��̃C���Q�[���B
		enStep_FlyCut,				//��s�J�b�g
		enStep_InGameSky,			//��ɂ���Ƃ��̃C���Q�[���B
		enStep_GameClearCut,		//�Q�[���N���A�J�b�g�B
		enStep_GameClearWaitFade,	//�Q�[���N���A�̂��������҂��B
	};
	Fade* m_fade = nullptr;				//���������B
	EnStep m_step = enStep_WaitFadeIn;	//�Q�[���X�e�b�v�B
	Bird* m_bird;						//�v���C���[
};

