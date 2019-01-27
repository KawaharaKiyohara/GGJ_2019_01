#include "stdafx.h"
#include "GameClearCut.h"
#include "Bird.h"

GameClearCut::GameClearCut()
{
	m_bird = FindGO<Bird>(GameObjectNames::BIRD);
}


GameClearCut::~GameClearCut()
{
	DeleteGO(m_ClearFontRender);
}

bool GameClearCut::Start()
{
	m_springCamera.Init(
		MainCamera(),
		2200.0f,
		false,
		0.0f
	);
	m_ClearFontRender = NewGO<prefab::CFontRender>(0);
	m_ClearNoFont = std::make_unique<DirectX::SpriteFont>(
		GraphicsEngine().GetD3DDevice(),
		L"font/hato_pop.spritefont"
		);
	m_ClearFontRender->SetFont(m_ClearNoFont.get());
	m_ClearFontRender->SetPosition(m_ClearFontPosition);
	m_ClearFontRender->SetPivot({ 0.5f, 0.5f });
	wchar_t stageName[256];
	swprintf(stageName, L"Stage Clear!!");
	m_ClearFontRender->SetText(stageName);
	m_ClearFontRender->SetColor({ 1.0f, 1.0f, 0.0f });
	m_ClearFontRender->SetShadowParam(true, 2.0f, CVector4::Black);
	m_ClearPosition = m_bird->GetPosition() + maepurasu;
	m_step = enStep_SpringCamera;
	return true;
}

void GameClearCut::Update()
{
	const float FONT_SPEED = 600;
	m_timer += GameTime().GetFrameDeltaTime();
	switch (m_step) {
	case enStep_SpringCamera:
		m_springCamera.SetPosition(m_ClearPosition);
		m_springCamera.SetTarget(m_bird->GetPosition());
		m_springCamera.SetDampingRate(1.0f);

		m_step = enStep_ClearmoziIn;
		break;
	case enStep_StageNoWait:
		if (m_timer > 2.0f) {
			m_step = enStep_effect;
		}
		break;
	case enStep_ClearmoziIn:
		m_ClearFontPosition.x += FONT_SPEED * GameTime().GetFrameDeltaTime();
		if (m_ClearFontPosition.x >= 0.0f) {
			m_ClearFontPosition.x = 0.0f;
			m_timer = 0.0f;
			m_step = enStep_StageNoWait;
		}
		m_ClearFontRender->SetPosition(m_ClearFontPosition);
		break;

	case enStep_effect:
		DeleteGO(this);
		break;
	}
	m_springCamera.Update();
}


