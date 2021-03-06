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
#include "GameClearCut.h"

Game::Game()
{
}


Game::~Game()
{
}
void Game::OnDestroy()
{
	DeleteGOs(GameObjectNames::DIRECTION_LIGHT);
	DeleteGOs(GameObjectNames::SKY);
	DeleteGO(GameObjectNames::BIRD);
	DeleteGO(GameObjectNames::HAWK_GENE);
	DeleteGO(GameObjectNames::CAMERA);
	DeleteGOs(GameObjectNames::SNAKE);
	DeleteGOs(GameObjectNames::FEED);
	DeleteGO(GameObjectNames::MAP);
	DeleteGO(m_groundBGM);
	DeleteGO(m_skyBgm);
	DeleteGO(m_snakeRender);
	DeleteGO(m_feedRender);
}
bool Game::Start()
{
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(100000.0f);
	MainCamera().SetPosition({ 10000.0f, 10000.0f, 0.0f });
	MainCamera().Update();
	
	//コリジョンのデバッグ表示を有効に。
//	dbg::SetDrawPhysicsCollisionEnable();
	CVector3 lightDir = { 1, -3, 1 };
	lightDir.Normalize();
	GraphicsEngine().GetShadowMap().SetLightDirection(lightDir);

	
	//ポストエフェクトを初期化する。
	InitPostEffects();
	//マップを構築する。
	InitMap();
	//空を作成。
	InitSky();
	//ディレクションライトを初期化。
	InitDirectionLight();

	//フェードのインスタンスをキャッシュ。
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
			//ゲームスタートカットが終わったので、実行ステップをインゲームにする。
			//鳥を初期化。
			InitBird();
			//ジャマーをテスト用に生成しておく。
			InitJammers();
			//カメラを初期化
			InitGameCamera();
			//餌を初期化
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
void Game::InitGameClearCut()
{
	auto go = NewGO<GameClearCut>(0,GameObjectNames::GAME_CLEAR_CUT);
	go->AddEventListener([&](IGameObject::SEventParam& eventParam) {
		if (eventParam.eEvent == IGameObject::enEvent_Destroy) {
			m_fade->StartFade({ 0.0f, 0.0f, 0.0f, 1.0f }, 1.0f);
			m_step = enStep_GameClearWaitFade;
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
	//Dofはとりあえず、無効かな。
	postEffect::Dof().Disable();
	//5フレームほどトーンマップを無効にしておく。
	postEffect::Tonemap().Disable(5);
}
void Game::InitSky()
{
	auto sky = NewGO<prefab::CSky>(0, GameObjectNames::SKY);
	sky->SetScale({ 100000.0f, 100000.0f, 100000.f });
	
}
void Game::InitJammers()
{
	//autoはC++11で追加された型推論という機能です。
	//コンパイラ構文から型を推論します。
	//hawkの型はHawk*、snakeの型はSnake*です。
	//鷹
	auto hawk = NewGO<HawkGene>(0, GameObjectNames::HAWK_GENE);

	float mapHalfSize = GameSettings::GetMapSize() * 0.5f;

	int numSnake = mapHalfSize * SNAKE_GEN_RATE;
	
	//蛇のレンダラの初期化。
	m_snakeRender = NewGO<prefab::CSkinModelRender>(0);
	m_snakeRender->Init(CmoFilePaths::SNAKE, nullptr, 0, enFbxUpAxisZ, numSnake);

	for (int i = 0; i < numSnake; i++) {
		auto snake = NewGO<Snake>(0, GameObjectNames::SNAKE);
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
	//マップサイズに比例して餌の数を決める。
	int numFeed = mapHalfSize * FEED_GEN_RATE;
	m_feedRender = NewGO<prefab::CSkinModelRender>(0);
	m_feedRender->Init(CmoFilePaths::FEED, nullptr, 0, enFbxUpAxisZ, numFeed);
	m_feedRender->SetShadowCasterFlag(true);
	m_feedRender->SetShadowReceiverFlag(true);
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
			DeleteGO(GameObjectNames::HAWK_GENE);
			InitGameClearCut();
			m_bird->SetStop();
		}
		break;
	case enStep_GameClearCut:
		
			
			//todo カリカリカリとりあえずｆａｄｅアウトして次。
			
		
		
		break;
	case enStep_GameClearWaitFade:
		if (!m_fade->IsFade()) {
			//ｆａｄｅが終わった
			int level = GameSettings::GetLevel() + 1;
			//todo クラッシュはまずいのでとりあえずループ
			GameSettings::SetLevel(level % GameSettings::GetNumLevel());
			DeleteGO(this);
			NewGO<Game>(0, GameObjectNames::GAME);
		}
		break;
	}
}