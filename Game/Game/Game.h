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
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CPhysicsStaticObject m_bgPhyStaticObject;
};

