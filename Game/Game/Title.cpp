#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Fade.h"

Title::Title()
{
}

Title::~Title()
{
	DeleteGO(m_spr);
	DeleteGO(m_bgm);
}
bool Title::Start()
{
	m_spr = NewGO<prefab::CSpriteRender>(0);
	m_spr->Init(
		L"sprite/title.dds",
		GraphicsEngine().Get2DSpaceScreenWidth(),
		GraphicsEngine().Get2DSpaceScreenHeight()
	);
	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init(L"sound/titleBgm.wav");
	m_bgm->Play(true);
	return true;
}
void Title::Update()
{
	switch (m_enStep) {
	case enStep_Disp:
		if (Pad(0).IsPressAnyKey()) {
			auto ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/press_key.wav");
			ss->Play(false);
			m_fade = FindGO<Fade>(GameObjectNames::FADE);
			m_fade->StartFade({ 0.0f, 0.0f, 0.0f, 1.0f }, 0.5f);
			m_enStep = enStep_WaitFade;
		}
		break;
	case enStep_WaitFade:
		m_timer = min( 0.5f, m_timer + GameTime().GetFrameDeltaTime());
		if (m_fade->IsFade() == false) {
			m_bgm->SetVolume(1.0f - (m_timer / 0.5f));
			NewGO<Game>(0, GameObjectNames::GAME);
			DeleteGO(this);
		}
		break;
	}

}


