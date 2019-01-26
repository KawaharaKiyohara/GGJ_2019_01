#pragma once

#include "tkEngine/camera/tkSpringCamera.h"

/// <summary>
/// ゲームスタートカット
/// </summary>
class GameStartCut : public IGameObject
{
public:
	GameStartCut();
	~GameStartCut();
	void Update() override;
	bool Start() override;
private:
	/// <summary>
	/// 実行ステップ。
	/// </summary>
	enum EnStep {
		enStep_AllView,		//全体を俯瞰中。
		enStep_ZoomIn,		//スタート地点にズームイン。
	};
	CVector3 m_startPosition = CVector3::Zero;	//開始地点。
	CSpringCamera m_springCamera;	//ばねカメラ。
	float m_timer = 0.0f;			//タイマー(単位：秒)
	EnStep m_step = enStep_AllView;	//全体を俯瞰中。
};

