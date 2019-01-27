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
#include "HawkGene.h"
Game::Game()
{
}


Game::~Game()
{
	DeleteGOs(GameObjectNames::DIRECTION_LIGHT);
	DeleteGOs(GameObjectNames::SKY);
	DeleteGO(GameObjectNames::BIRD);
	DeleteGO(GameObjectNames::HAWK_GENE);
	DeleteGO(GameObjectNames::CAMERA);
	DeleteGO(m_groundBGM);
	DeleteGO(m_skyBgm);
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
	CVector3 lightDir = { 1, -3, 1 };
	lightDir.Normalize();
	GraphicsEngine().GetShadowMap().SetLightDirection(lightDir);


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
	m_fade->StartFade({ 0.0f, 0.0f, 0.0f, 0.0f }, 1.0f);

	auto& shadowMap = GraphicsEngine().GetShadowMap();
	shadowMap.SetLightHeight(GameSettings::GetShadowMapLightHeightInStartCut());
	
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
			InitJammers();
			//�J������������
			InitGameCamera();
			//�a��������
			InitFeed();
			postEffect::Dof().Enable();
			postEffect::Dof().SetDofRangeParam(0, 150, 600, 1800);
			postEffect::Dof().SetBokeLuminance(0.6f);
			postEffect::Dof().SetHexaBokeRadius(3.0f);
			m_fade->StartFade({ 0.0f, 0.0f, 0.0f, 0.0f }, 0.5f);
			SEventParam param;
			param.eEvent = (EnEvent)enGameEvent_StartInGameGround;
			param.gameObject = this;
			//
			for (auto& listener : m_eventListeners) {
				listener(param);
			}
			auto& shadowMap = GraphicsEngine().GetShadowMap();
			shadowMap.SetLightHeight(GameSettings::GetShadowMapLightHeightInGame());
			m_groundBGM = NewGO<prefab::CSoundSource>(0);
			m_groundBGM->Init(L"sound/groundBgmInGame.wav");
			m_groundBGM->Play(true);
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
void Game::InitJammers()
{
	//auto��C++11�Œǉ����ꂽ�^���_�Ƃ����@�\�ł��B
	//�R���p�C���\������^�𐄘_���܂��B
	//hawk�̌^��Hawk*�Asnake�̌^��Snake*�ł��B
	//��
	auto hawk = NewGO<HawkGene>(0, GameObjectNames::HAWK_GENE);

	float mapHalfSize = GameSettings::GetMapSize() * 0.5f;

	int numSnake = mapHalfSize * SNAKE_GEN_RATE;
	for (int i = 0; i < numSnake; i++) {
		auto snake = NewGO<Snake>(0);
		snake->m_pos = CVector3::Zero;
		snake->m_pos.x = CMath::Lerp(Random().GetRandDouble(), mapHalfSize, -mapHalfSize);
		snake->m_pos.y = 0.0f;
		snake->m_pos.z = CMath::Lerp(Random().GetRandDouble(), mapHalfSize, -mapHalfSize);
	}
	
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
	float mapHalfSize = GameSettings::GetMapSize() * 0.5f;
	//�}�b�v�T�C�Y�ɔ�Ⴕ�ĉa�̐������߂�B
	int numFeed = mapHalfSize * FEED_GEN_RATE;
	for (int i = 0; i < numFeed; i++) {
		auto feed = NewGO<Feed>(0, GameObjectNames::FEED);
		auto pos = CVector3::Zero;
		pos.x = CMath::Lerp(Random().GetRandDouble(), mapHalfSize, -mapHalfSize);
		pos.y = 0.0f;
		pos.z = CMath::Lerp(Random().GetRandDouble(), mapHalfSize, -mapHalfSize);
		feed->SetPosition(pos);
	}
}

void Game::Update()
{
	switch (m_step) {
	case enStep_WaitFadeIn:
		if (!m_fade->IsFade()) {
			InitGameStartCut();
			m_step = enStep_StartCut;
		}
		break;
	case enStep_StartCut:
		break;
	case enStep_InGameGround:
		if (m_bird->isAdult()) {
			m_timer = 0.0f;
			m_skyBgm = NewGO < prefab::CSoundSource>(0);
			m_skyBgm->Init(L"sound/skyBgmInGame.wav");
			m_skyBgm->Play(true);
			m_step = enStep_InGameSky;
		}
		break;
	case enStep_InGameSky:
		if (m_groundBGM != nullptr) {
			m_timer += GameTime().GetFrameDeltaTime();
			if (m_timer >= 0.5f) {
				DeleteGO(m_groundBGM);
				m_groundBGM = nullptr;
				m_skyBgm->SetVolume(1.0f);
			}
			else {
				m_groundBGM->SetVolume(1.0f - (m_timer / 0.5f));
				m_skyBgm->SetVolume((m_timer / 0.5f));
			}
		}
		
		if (( m_bird->GetPosition() - GameSettings::GetGoalPosition()).Length()<= 200.0f) {
			m_step = enStep_GameClearCut;
			m_bird->SetStop();
		}
		break;
	case enStep_GameClearCut:
		//todo �J���J���J���Ƃ肠�������������A�E�g���Ď��B
		m_fade->StartFade({0.0f, 0.0f, 0.0f, 1.0f}, 1.0f);
		m_step = enStep_GameClearWaitFade;
		break;
	case enStep_GameClearWaitFade:
		if (!m_fade->IsFade()) {
			//�����������I�����
			int level = GameSettings::GetLevel() + 1;
			//todo �N���b�V���͂܂����̂łƂ肠�������[�v
			GameSettings::SetLevel(level % GameSettings::GetNumLevel());
			DeleteGO(this);
			NewGO<Game>(0, GameObjectNames::GAME);
		}
		break;
	}
}