#include "stdafx.h"
#include "GameStartCut.h"
#include "Fade.h"

GameStartCut::GameStartCut()
{
}

GameStartCut::~GameStartCut()
{
	DeleteGO(m_bgm);
	DeleteGO(m_stageFontRender);
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
	m_stageFontRender = NewGO<prefab::CFontRender>(0);
	m_stageNoFont = std::make_unique<DirectX::SpriteFont>(
		GraphicsEngine().GetD3DDevice(),
		L"font/hato_pop.spritefont"
		);
	m_stageFontRender->SetFont(m_stageNoFont.get());
	m_stageFontRender->SetPosition(m_stageFontPosition);
	m_stageFontRender->SetPivot({ 0.5f, 0.5f });
	wchar_t stageName[256];
	swprintf(stageName, L"Stage %d", GameSettings::GetLevel() + 1);
	m_stageFontRender->SetText(stageName);
	m_stageFontRender->SetColor({ 1.0f, 1.0f, 0.0f });
	m_stageFontRender->SetShadowParam(true, 2.0f, CVector4::Black);
	m_step = enStep_StageNoIn;
	return true;
}

void GameStartCut::Update()
{
	const float FONT_SPEED = 600;
	m_timer += GameTime().GetFrameDeltaTime();
	switch (m_step) {
	case enStep_StageNoIn:
		m_stageFontPosition.x += FONT_SPEED * GameTime().GetFrameDeltaTime();
		if (m_stageFontPosition.x >= 0.0f) {
			m_stageFontPosition.x = 0.0f;
			m_timer = 0.0f;
			m_step = enStep_StageNoWait;
			
		}
		m_stageFontRender->SetPosition(m_stageFontPosition);
		break;
	case enStep_StageNoWait:
		if (m_timer > 2.0f) {
			m_step = enStep_StageNoOut;
		}
		break;
	case enStep_StageNoOut:
		m_stageFontPosition.x += FONT_SPEED * GameTime().GetFrameDeltaTime();
		if (m_stageFontPosition.x >= 1200.0f) {
			m_stageFontPosition.x = 1200.0f;
			m_timer = 0.0f;
			m_step = enStep_AllView;
		}
		m_stageFontRender->SetPosition(m_stageFontPosition);
		break;
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

