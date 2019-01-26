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
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(100000.0f);
	MainCamera().SetPosition({ 10000.0f, 10000.0f, 0.0f });
	MainCamera().Update();
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(CmoFilePaths::GROUND);
	m_skinModelRender->SetShadowReceiverFlag(true);
	m_bgPhyStaticObject.CreateMesh(CVector3::Zero, CQuaternion::Identity, CVector3::One, m_skinModelRender);
	//コリジョンのデバッグ表示を有効に。
	dbg::SetDrawPhysicsCollisionEnable();

	GraphicsEngine().GetShadowMap().SetLightDirection({ 0.707f, -0.707f, 0.0f });

	//todo 難易度を仮決定。
	//todo 最終的には、ステージ選択的な感じ？
	GameSettings::SetLevel(0);

	//ポストエフェクトを初期化する。
	InitPostEffects();
	//マップを構築する。
	InitMap();
	//空を作成。
	InitSky();
	//ディレクションライトを初期化。
	InitDirectionLight();
	//鳥を初期化。
	InitBird();
	//ジャマーをテスト用に生成しておく。
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
void Game::Update()
{
}