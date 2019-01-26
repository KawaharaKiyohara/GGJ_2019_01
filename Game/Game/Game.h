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
	/// ポストエフェクトを初期化。
	/// </summary>
	void InitPostEffects();
	/// <summary>
	/// ディレクションライトを初期化。
	/// </summary>
	void InitDirectionLight();
	/// <summary>
	/// 空を初期化。
	/// </summary>
	void InitSky();
	/// <summary>
	/// 鳥を初期化。
	/// </summary>
	void InitBird();
	/// <summary>
	/// ジャマーたちをテスト用に生成しとくか。
	/// </summary>
	void InitTestJammers();
	/// <summary>
    /// ゲームカメラを初期化
    /// </summary>
	void InitGameCamera();
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CPhysicsStaticObject m_bgPhyStaticObject;
};

