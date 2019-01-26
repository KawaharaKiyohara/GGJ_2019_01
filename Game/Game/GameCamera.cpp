#include "stdafx.h"
#include "GameCamera.h"
#include "Bird.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
#include <math.h> 
GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	//カメラのニアクリップとファークリップを設定する。
	//ニアクリップとファークリップの間がカメラの映す範囲になる
	MainCamera().SetNear(1.0f);     //ニアクリップ　カメラから近いほうの面
	MainCamera().SetFar(100000.0f);  //ファークリップ　カメラから遠いほうの面
	return true;
}

void GameCamera::Update()
{
	if (m_bird == nullptr) {
		m_bird = FindGO<Bird>(GameObjectNames::BIRD);
	}
	TPS();
	//視点
	MainCamera().SetTarget(m_target);
	//座標
	MainCamera().SetPosition(m_position);
	//カメラの更新。
	MainCamera().Update();
}

void GameCamera::TPS()
{
	if (!m_bird->isAdult()) {
		CVector3 stickR;
		stickR.x = -Pad(0).GetRStickXF();	//アナログスティックのxの入力量を取得。
		stickR.y = Pad(0).GetRStickYF();	//アナログスティックのxの入力量を取得。
		stickR.z = 0.0f;
		//右スティックの入力
		//右スティック
		m_sdegreexz = -stickR.x * 2.0f*30.0f*GameTime().GetFrameDeltaTime();
		m_sdegreey = -stickR.y * 2.0f*30.0f*GameTime().GetFrameDeltaTime();
	}
	else {
		CVector3 stickL;
		stickL.x = -Pad(0).GetLStickXF();	//アナログスティックのxの入力量を取得。
		stickL.y = Pad(0).GetLStickYF();	//アナログスティックのxの入力量を取得。
		stickL.z = 0.0f;
		//右スティックの入力
		//右スティック
		m_sdegreexz = -stickL.x * 2.0f*30.0f*GameTime().GetFrameDeltaTime();
		m_sdegreey = -stickL.y*2.0f*30.0f*GameTime().GetFrameDeltaTime();
	}
	//回転度加算
	m_degreexz += m_sdegreexz;
	m_degreey += m_sdegreey;
	//上下方向のカメラ移動を制限
	if (m_degreey >= 70.0f) {
		m_degreey = 70.0f;
	}
	if (m_degreey <= -15.0f) {
		m_degreey = -15.0f;
	}
	//角度をラジアン単位に直す
	m_radianx = M_PI / 180 * m_degreexz;
	m_radiany = M_PI / 180 * m_degreey;
	m_target = m_bird->GetPosition() + m_bird->GetRight()*30.0f;
	m_target.y += 40.0f;
	//Y軸周りに回転させる。
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, m_radianx);
	m_topos = { 0.0f, 0.0f, 1.0f };
	qRot.Multiply(m_topos);
	//上下の回転。
	//まずは回す軸を計算する。
	CVector3 rotAxis;
	rotAxis.Cross(m_topos, CVector3::AxisY);
	//ベクトルを正規化する。
	rotAxis.Normalize();
	qRot.SetRotation(rotAxis, m_radiany);
	qRot.Multiply(m_topos);
	m_topos *= m_r;
	m_position = m_target + m_topos;
}
