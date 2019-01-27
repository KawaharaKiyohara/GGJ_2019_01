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
	/// ジャマーたちを生成しとくか。
	/// </summary>
	void InitJammers();
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

	/// <summary>
	/// ゲームクリアカット演出を作成。
	/// </summary>
	void InitGameClearCut();

	/// 餌を初期化
    /// </summary>
	void InitFeed();
private:
	/// <summary>
	/// ゲームステップ。
	/// </summary>
	enum EnStep {
		enStep_WaitFadeIn,			//フェードイン町。
		enStep_StartCut,			//開始カット
		enStep_InGameGround,		//地面にいるときのインゲーム。
		enStep_FlyCut,				//飛行カット
		enStep_InGameSky,			//空にいるときのインゲーム。
		enStep_GameClearCut,		//ゲームクリアカット。
		enStep_GameClearWaitFade,	//ゲームクリアのｆａｄｅ待ち。
	};
	Fade* m_fade = nullptr;				//ｆａｄｅ。
	EnStep m_step = enStep_WaitFadeIn;	//ゲームステップ。
	Bird* m_bird;						//プレイヤー
};

