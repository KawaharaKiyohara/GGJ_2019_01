#pragma once
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class GameCamera;
class Bird : public IGameObject
{
public:
	Bird();
	~Bird();
	bool Start() override;
	void Update() override;
	void Turn();
	void SetAnimation();
	void AnimationController();
	void Move();
	void Animation();
	//プレイヤーの座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//プレイヤーの座標を取得
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//プレイヤーを停止させる
	void Stop()
	{
		m_stop = true;
	}
	//プレイヤーの真右のベクトルを取得
	CVector3 GetRight() const
	{
		return m_birdright;
	}
	//プレイヤーの後方のベクトルを取得
	CVector3 GetBack() const
	{
		return m_birdback;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = { 00.0f,100.0f,0.0f };
	CVector3 m_movespeed = { 0.0f,0.0f,0.0f };
	CQuaternion m_rotation = CQuaternion::Identity;
	CQuaternion m_rotation2 = CQuaternion::Identity;
	CVector3 m_scale = CVector3::One;
	//プレイヤーの向きと平行なベクトル
	CVector3 m_player_heikou;
	CVector3 m_birdright;
	CVector3 m_birdback;
	CCharacterController m_charaCon;
	//アニメーション
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_damage,
		enAnimationClip_KneelDown,
		enAnimationClip_num,
	};
	//アニメーション分岐
	enum EnState {
		enState_Idle,
		enState_Walk,
		enState_GameOver,
		enState_Damage,
		enState_Eat,
	};
	CAnimationClip m_animClip[enAnimationClip_num];
	EnState m_state = enState_Idle;
	float m_degree = 180.0f;
	float m_radian = 0;
	bool m_stop = false;
	float m_multiply = 40.0f;
	float m_damagetimer = 0.0f;
	float m_blinktimer = 0.0f;
	GameCamera* m_gamecamera = nullptr;

};

