#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Bird.h"
#include "Hawk.h"
#include "Snake.h"
#include "Map.h"
#include "GameCamera.h"
#include "GameStartCut.h"
#include "Feed.h"
#include "Fade.h"

Game::Game()
{
}


Game::~Game()
{
	DeleteGOs(GameObjectNames::DIRECTION_LIGHT);
	DeleteGOs(GameObjectNames::SKY);
	DeleteGO(GameObjectNames::BIRD);
	DeleteGO(GameObjectNames::HAWK);
	DeleteGO(GameObjectNames::GAME_START_CUT);
}
bool Game::Start()
{
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(100000.0f);
	MainCamera().SetPosition({ 10000.0f, 10000.0f, 0.0f });
	MainCamera().Update();
	
	//�R���W�����̃f�o�b�O�\����L���ɁB
//	dbg::SetDrawPhysicsCollisionEnable();

	GraphicsEngine().GetShadowMap().SetLightDirection({ 0.707f, -0.707f, 0.0f });

	//todo ��Փx��������B
	//todo �ŏI�I�ɂ́A�X�e�[�W�I��I�Ȋ����H
	GameSettings::SetLevel(0);

	//�Q�[���J�n�J�b�g�̍쐬�B
	InitGameStartCut();
	//�|�X�g�G�t�F�N�g������������B
	InitPostEffects();
	//�}�b�v���\�z����B
	InitMap();
	//����쐬�B
	InitSky();
	//�f�B���N�V�������C�g���������B
	InitDirectionLight();

	//�t�F�[�h�̃C���X�^���X���L���b�V���B
	m_fade = FindGO<Fade>(GameObjectNames::FADE);

	return true;
}
void Game::InitGameStartCut()
{
	auto go = NewGO<GameStartCut>(0, GameObjectNames::GAME_START_CUT);
	go->AddEventListener([&](IGameObject::SEventParam& eventParam) {
		if (eventParam.eEvent == IGameObject::enEvent_Destroy) {
			//�Q�[���X�^�[�g�J�b�g���I������̂ŁA���s�X�e�b�v���C���Q�[���ɂ���B
			//�����������B
			InitBird();
			//�W���}�[���e�X�g�p�ɐ������Ă����B
			InitTestJammers();
			//�J������������
			InitGameCamera();
			//�a��������
			InitFeed();
			m_fade->StartFade({ 0.0f, 0.0f, 0.0f, 0.0f }, 0.5f);
			m_step = enStep_InGameGround;
		}
	});
}
void Game::InitMap()
{
	NewGO<Map>(0, GameObjectNames::MAP);
}
void Game::InitBird()
{
	m_bird = NewGO<Bird>(0, GameObjectNames::BIRD);
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

void Game::InitGameCamera()
{
	NewGO<GameCamera>(0, GameObjectNames::CAMERA);
}

void Game::InitFeed()
{
	NewGO<Feed>(0, GameObjectNames::FEED);
}

void Game::Update()
{
	switch (m_step) {
	case enStep_StartCut:
		break;
	case enStep_InGameGround:
		if (m_bird->isAdult()) {
			m_step = enStep_InGameSky;
		}
		break;
	case enStep_InGameSky:
		if (( m_bird->GetPosition() - GameSettings::GetGoalPosition()).Length()<= 200.0f) {
			m_step = enStep_GameClearCut;
			m_bird->SetStop();
		}
		break;
	case enStep_GameClearCut:
		break;
	}
}