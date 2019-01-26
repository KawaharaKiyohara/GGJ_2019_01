#include "stdafx.h"
#include "GameStartCut.h"
#include "Fade.h"

GameStartCut::GameStartCut()
{
}

GameStartCut::~GameStartCut()
{
	DeleteGO(m_bgm);
}

bool GameStartCut::Start()
{
	m_springCamera.Init(
		MainCamera(),
		2200.0f,
		false,
		0.0f
	);
	//ゲーム開始座標をランダムで決定する。
	auto halfMapSize = GameSettings::GetMapSize() * 0.5f;
	m_startPosition.x = CMath::Lerp(Random().GetRandDouble(), -halfMapSize, halfMapSize);
	m_startPosition.y = 200.0f;
	m_startPosition.z = CMath::Lerp(Random().GetRandDouble(), -halfMapSize, halfMapSize);
	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init(L"sound/GameStartCutBGM.wav");
	m_bgm->Play(true);
	return true;
}

void GameStartCut::Update()
{
	m_timer += GameTime().GetFrameDeltaTime();
	switch (m_step) {
	case enStep_AllView:
		
		if (m_timer > 2.0f) {
			auto target = m_startPosition + CVector3::AxisX * -1.0f;
			m_springCamera.SetPosition(m_startPosition);
			m_springCamera.SetTarget(target);
			m_springCamera.SetDampingRate(1.0f);
			
			m_step = enStep_ZoomIn_0;
		}
		break;
	case enStep_ZoomIn_0:
		m_bgm->SetVolume(1.0f - min(1.0f, m_timer / 5.0f));

		if (m_timer > 5.0f) {
			//ｆａｄｅ開始
			FindGO<Fade>(GameObjectNames::FADE)->StartFade(
				{ 0.0f, 0.0f, 0.0f, 1.0f }, 0.5f);
			m_step = enStep_ZoomIn_1;
		}
		break;
	case enStep_ZoomIn_1:
		//ズームイン。
		if (m_timer > 6.0f) {
			m_startPosition.y = 0.0f;
			GameSettings::SetStartPosition(m_startPosition);
			DeleteGO(this);
		}
		break;
	}
	m_springCamera.Update();
}

