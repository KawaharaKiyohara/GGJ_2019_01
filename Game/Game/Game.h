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
	/// マップを構築する。
	/// </summary>
	void InitMap();

    /// ゲームカメラを初期化
    /// </summary>
	void InitGameCamera();
	/// <summary>
	/// ゲーム開始カット演出を作成。
	/// </summary>
	void InitGameStartCut();
private:
	/// <summary>
	/// ゲームステップ。
	/// </summary>
	enum EnStep {
		enStep_StartCut,		//開始カット
		enStep_InGameGround,	//地面にいるときのインゲーム。
		enStep_FlyCut,			//飛行カット
		enStep_InGameSky,		//空にいるときのインゲーム。
		enStep_GameClearCut,	//ゲームクリアカット。
	};
	EnStep m_step = enStep_StartCut;	//ゲームステップ。
};

