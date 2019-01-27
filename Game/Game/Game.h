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
	void OnDestroy();
	bool Start();
	void Update();
	void UpdateSnakeInstancingData(CVector3 trans, CQuaternion rot, CVector3 scale	)
	{
		m_snakeRender->UpdateInstancingData(trans, rot, scale);
	}
	void UpdateFeedInstancingData(CVector3 trans, CQuaternion rot, CVector3 scale)
	{
		m_feedRender->UpdateInstancingData(trans, rot, scale);
	}
	void SetFeedEmissionColor(CVector3 emissionColor)
	{
		m_feedRender->SetEmissionColor(emissionColor);
	}
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
	/// 餌を初期化
    /// </summary>
	void InitFeed();
public:
	enum EnGameEvent {
		enGameEvent_StartInGameGround,	//地面にいるときのインゲームが開始された。
	};
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
	prefab::CSoundSource* m_groundBGM = nullptr;	//地面にいるときのBGM
	prefab::CSoundSource* m_skyBgm = nullptr;		//空にいるときのBGM
	prefab::CSkinModelRender* m_snakeRender = nullptr;	//蛇のレンダリング。
	prefab::CSkinModelRender* m_feedRender = nullptr;	//餌のレンダリング。
	float m_timer = 0.0f;
};

