#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Bird.h"
#include "Hawk.h"
#include "Snake.h"
#include "Map.h"

Game::Game()
{
}


Game::~Game()
{
	DeleteGOs(GameObjectNames::DIRECTION_LIGHT);
	DeleteGOs(GameObjectNames::SKY);
	DeleteGO(GameObjectNames::BIRD);
	DeleteGO(GameObjectNames::HAWK);
}
bool Game::Start()
{
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(100000.0f);
	MainCamera().SetPosition({ 10000.0f, 10000.0f, 0.0f });
	MainCamera().Update();
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(CmoFilePaths::GROUND);
	m_skinModelRender->SetShadowReceiverFlag(true);
	m_bgPhyStaticObject.CreateMesh(CVector3::Zero, CQuaternion::Identity, CVector3::One, m_skinModelRender);
	//�R���W�����̃f�o�b�O�\����L���ɁB
	dbg::SetDrawPhysicsCollisionEnable();

	GraphicsEngine().GetShadowMap().SetLightDirection({ 0.707f, -0.707f, 0.0f });

	//todo ��Փx��������B
	//todo �ŏI�I�ɂ́A�X�e�[�W�I��I�Ȋ����H
	GameSettings::SetLevel(0);

	//�|�X�g�G�t�F�N�g������������B
	InitPostEffects();
	//�}�b�v���\�z����B
	InitMap();
	//����쐬�B
	InitSky();
	//�f�B���N�V�������C�g���������B
	InitDirectionLight();
	//�����������B
	InitBird();
	//�W���}�[���e�X�g�p�ɐ������Ă����B
	InitTestJammers();

	return true;
}
void Game::InitMap()
{
	NewGO<Map>(0, GameObjectNames::MAP);
}
void Game::InitBird()
{
	NewGO<Bird>(0, GameObjectNames::BIRD);
}
void Game::InitPostEffects()
{
	//Dof�͂Ƃ肠�����A�������ȁB
	postEffect::Dof().Disable();
	//5�t���[���قǃg�[���}�b�v�𖳌��ɂ��Ă����B
	postEffect::Tonemap().Disable(5);
}
void Game::InitSky()
{
	auto sky = NewGO<prefab::CSky>(0, GameObjectNames::SKY);
	sky->SetScale({ 50000.0f, 50000.0f, 50000.f });
	
}
void Game::InitTestJammers()
{
	//auto��C++11�Œǉ����ꂽ�^���_�Ƃ����@�\�ł��B
	//�R���p�C���\������^�𐄘_���܂��B
	//hawk�̌^��Hawk*�Asnake�̌^��Snake*�ł��B
	//��
	auto hawk = NewGO< Hawk>(0);

	auto snake = NewGO<Snake>(0);

}
void Game::InitDirectionLight()
{
	auto dirLig = NewGO<prefab::CDirectionLight>(0, GameObjectNames::DIRECTION_LIGHT);
	dirLig->SetDirection({ 0.707f, -0.707f, 0.0f });
	dirLig->SetColor({ 0.8f, 0.8f, 0.8f, 1.0f });

}
void Game::Update()
{
}