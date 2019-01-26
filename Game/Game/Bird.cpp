#include "stdafx.h"
#include "Bird.h"
#include "GameCamera.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
#include <math.h> 		
#include "Feed.h"
#include "GameSettings.h"

Bird::Bird()
{
}


Bird::~Bird()
{
	DeleteGO(m_skinModelRender);
}
void Bird::SetAnimation()
{
	m_animClip[enAnimationClip_idle].Load(L"animData/unityChan/idle.tka");
	m_animClip[enAnimationClip_walk].Load(L"animData/unityChan/walk.tka");
	m_animClip[enAnimationClip_damage].Load(L"animData/unityChan/damage.tka");
	for (auto& animClip : m_animClip) {
		animClip.SetLoopFlag(true);
	}
	m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisY);

}

bool Bird::Start()
{
	//SetAnimation();
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(CmoFilePaths::BIRD);
	//シャドウキャスターとシャドウレシーバーのフラグを立てる。
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	m_position = GameSettings::GetStartPosition();
	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		20.0,			//半径。 
		30.0f,			//高さ。
		m_position		//初期位置。
	);
	return true;
}

void Bird::Update()
{
	if (!m_stop) {
		AnimationController();
		CQuaternion qRot;
		qRot.SetRotationDeg(m_birdright, m_degreey);
		m_rotation.Multiply(qRot);
	}
	if (m_charaCon.IsOnGround()) {
		//地面についた。
		m_movespeed.y = 0.0f;
	}
	Sound();
	m_charaCon.SetPosition(m_position);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
}

void Bird::Move()
{
	if (m_adult) {
		m_movespeed = MainCamera().GetForward()*m_multiply*60.0f*GameTime().GetFrameDeltaTime();
	}
	else {
		//左スティックの入力量を取得
		CVector3 stickL;
		//ダメージを受けているとき、ゲームオーバーの時、ゲームクリアの時は右スティックの入力を無効にする
		if (m_state == enState_GameOver || m_state == enState_Eat) {
			stickL.x = 0.0f;
			stickL.y = 0.0f;
		}
		else {
			stickL.y = Pad(0).GetLStickYF();
			stickL.x = -Pad(0).GetLStickXF();	//アナログスティックの入力量を取得。
		}
		//左スティック
		//スティックの左右入力の処理
		m_movespeed.z = 0.0f;
		m_movespeed.x = 0.0f;
		m_movespeed.z = +sin(m_radian)*stickL.x * m_multiply;
		m_movespeed.x = -cos(m_radian)*stickL.x * m_multiply;
		//スティックの上下入力の処理
		m_movespeed.z += cos(m_radian)*stickL.y * m_multiply;
		m_movespeed.x += sin(m_radian)*stickL.y * m_multiply;
		m_movespeed.y = 0.0f;
		//重力
		//m_movespeed.y -= 800.0f *GameTime().GetFrameDeltaTime();
		//キャラクターコントローラーを使用して、座標を更新。
	}
	m_position = m_charaCon.Execute(m_movespeed, GameTime().GetFrameDeltaTime());
}

void Bird::Turn()
{
	if (m_adult) {
		//左スティックの入力量を取得
		CVector3 stickL;
		stickL.y = Pad(0).GetLStickYF();
		stickL.x = -Pad(0).GetLStickXF();	//アナログスティックの入力量を取得。
			//自機の角度の差分
		float sdegree = 0.0f;
		sdegree = -stickL.x * 2.0f*30.0f*GameTime().GetFrameDeltaTime();
		//回転処理
		m_degree += sdegree;
		m_rotation.SetRotationDeg(CVector3::AxisY, m_degree);
	}
	else {
		m_gamecamera = FindGO<GameCamera>(GameObjectNames::CAMERA);
		if (m_gamecamera == nullptr) {
			return;
		}
		CVector3 rotation = { 0.0f,0.0f,0.0f };
		//自機の角度の差分
		float sdegree = 0.0f;
		m_radian = M_PI / 180 * m_degree;
		//右スティック
		CVector2 stickR;
		stickR.x = -Pad(0).GetRStickXF();	//アナログスティックのxの入力量を取得。
		stickR.y = Pad(0).GetRStickYF();
		//向き
		//右スティック
		sdegree = -stickR.x * 2.0f*30.0f*GameTime().GetFrameDeltaTime();
		//回転処理
		m_degree += sdegree;
		m_rotation.SetRotationDeg(CVector3::AxisY, m_degree);
	}
	CVector3 moveSpeedXZ = { 0.0f,0.0f,1.0f };
	m_rotation.Multiply(moveSpeedXZ);
	m_player_heikou = moveSpeedXZ;
	m_birdright = moveSpeedXZ;
	m_birdback = moveSpeedXZ;
	//プレイヤーの右のベクトル
	m_birdright = moveSpeedXZ;
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 90.0f);
	qRot.Multiply(m_birdright);
	//プレイヤーの後ろのベクトル
	CQuaternion qRot2;
	qRot2.SetRotationDeg(CVector3::AxisY, 180.0f);
	qRot2.Multiply(m_birdback);
	//m_movespeedからキャラクターを回転させる
	/*auto moveSpeedXZ = m_movespeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	moveSpeedXZ.y = 0;
	if (moveSpeedXZ.LengthSq() < 0.5f) {
		return;
	}
	m_player_heikou = moveSpeedXZ;
	m_birdright = moveSpeedXZ;
	m_birdback = moveSpeedXZ;
	//プレイヤーの右のベクトル
	m_birdright= moveSpeedXZ;
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 90.0f);
	qRot.Multiply(m_birdright);
	//プレイヤーの後ろのベクトル
	CQuaternion qRot2;
	qRot2.SetRotationDeg(CVector3::AxisY, 180.0f);
	qRot2.Multiply(m_birdback);
	m_rotation.SetRotation({ 0.0f,1.0f,0.0f }, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	m_skinModelRender->SetRotation(m_rotation);*/
}

void Bird::Sound()
{
	/*if (m_eating) {
		prefab::CSoundSource* ss;
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/eat.wav");
		ss->Play(false);
		m_eating = false;
	}*/
	if (m_state == enState_Eat) {
		if (m_soundtimer >= m_eatingtime) {
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/eat.wav");
			ss->Play(false);
			m_eating = false;
			m_soundtimer = 0.0f;
		}
		m_soundtimer += 30.0f*GameTime().GetFrameDeltaTime();
	}
	else if (m_state == enState_Walk) {
		if (m_soundtimer >= m_walktime) {
			prefab::CSoundSource* ss;
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/cry.wav");
			ss->Play(false);
			m_soundtimer = 0.0f;
		}
		m_soundtimer += 30.0f*GameTime().GetFrameDeltaTime();
	}
	else {
		m_soundtimer = 0.0f;
	}
}

void Bird::Animation()
{
	if (Pad(0).IsTrigger(enButtonX)) {
		m_state = enState_Damage;
	}
	if (Pad(0).IsTrigger(enButtonA)) {
		m_state = enState_Eat;
	}
	if (Pad(0).IsTrigger(enButtonY)) {
		if (m_adult) {
			m_adult = false;
		}
		else {
			m_adult = true;
		}
	}
	QueryGOs<Feed>(GameObjectNames::FEED, [&](Feed* feed) {
		CVector3 pos = feed->GetPosition() - m_position;
		if (pos.Length() <= 70.0f) {
			m_state = enState_Eat;
			m_feed = feed;
			return false;
		}
		return true;
	});
}

void Bird::AnimationController()
{
	//ステート分岐によってアニメーション再生を分岐
	switch (m_state) {
	case enState_Walk:
	case enState_Idle:
		if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
			//歩きモーション。
			//m_skinModelRender->PlayAnimation(enAnimationClip_walk, 0.2f);
		}
		else {
			//待機モーション
			//m_skinModelRender->PlayAnimation(enAnimationClip_idle, 0.2f);
		}
		if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
			m_state = enState_Walk;
		}
		else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
			m_state = enState_Idle;
		}
		Move();
		Turn();
		Animation();
		break;
	case enState_Damage:
		/*if (m_skinModelRender->IsPlayingAnimation()) {
			//m_skinModelRender->PlayAnimation(enAnimationClip_damage, 0.2f);
		}
		else {
			//アニメーションの再生が終わったら、再びアニメーション分岐
			if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
				m_state = enState_Walk;
			}
			else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
				m_state = enState_Idle;
			}
		}*/
		m_damagetimer += GameTime().GetFrameDeltaTime();
		m_blinktimer += GameTime().GetFrameDeltaTime();
		if (m_blinktimer >= 0.05f) {
			//0.2秒経過
			bool isActive = m_skinModelRender->IsActive();
			m_skinModelRender->SetActiveFlag(!isActive);
			m_blinktimer = 0.0f;
		}
		if (m_damagetimer >= 0.7f) {
			//2秒経過したのでダメージ表現終わり。
			m_skinModelRender->SetActiveFlag(true);
			m_damagetimer = 0.0f;
			m_blinktimer = 0.0f;
			//アニメーションの再生が終わったら、再びアニメーション分岐
			if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
				m_state = enState_Walk;
			}
			else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
				m_state = enState_Idle;
			}
		}
		Move();
		//キャラクターの向き関係
		Turn();
		break;
	case enState_Eat:
		if (m_eattime >= m_eattimer) {
			CQuaternion qRot;
			if (m_eattimer * 2 >= m_eattime) {
				if (m_feed != nullptr) {
					DeleteGO(m_feed);
					m_feed = nullptr;
					m_feedcount++;
					m_eating = true;
				}
				m_degreey -= 1.8f;
				qRot.SetRotationDeg(m_birdright, m_degreey);
			}
			else {
				m_degreey += 1.8f;
				qRot.SetRotationDeg(m_birdright, m_degreey);
			}
			m_eattimer += 60.0f* GameTime().GetFrameDeltaTime();
		}
		else {
			m_eat = false;
			m_eattimer = 0.0f;
			if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
				m_state = enState_Walk;
			}
			else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
				m_state = enState_Idle;
			}
		}
		Turn();
		break;
	}
}

