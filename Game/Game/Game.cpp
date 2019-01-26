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
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(100000.0f);
	MainCamera().SetPosition({ 10000.0f, 10000.0f, 0.0f });
	MainCamera().Update();
	
	//コリジョンのデバッグ表示を有効に。
//	dbg::SetDrawPhysicsCollisionEnable();

	GraphicsEngine().GetShadowMap().SetLightDirection({ 0.707f, -0.707f, 0.0f });

	//todo 難易度を仮決定。
	//todo 最終的には、ステージ選択的な感じ？
	GameSettings::SetLevel(0);

	//ゲーム開始カットの作成。
	InitGameStartCut();
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
			InitTestJammers();
			//カメラを初期化
			InitGameCamera();
			//餌を初期化
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
	//Dofはとりあえず、無効かな。
	postEffect::Dof().Disable();
	//5フレームほどトーンマップを無効にしておく。
	postEffect::Tonemap().Disable(5);
}
void Game::InitSky()
{
	auto sky = NewGO<prefab::CSky>(0, GameObjectNames::SKY);
	sky->SetScale({ 50000.0f, 50000.0f, 50000.f });
	
}
void Game::InitTestJammers()
{
	//autoはC++11で追加された型推論という機能です。
	//コンパイラ構文から型を推論します。
	//hawkの型はHawk*、snakeの型はSnake*です。
	//鷹
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