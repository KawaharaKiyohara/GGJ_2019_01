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
}
bool Title::Start()
{
	m_spr = NewGO<prefab::CSpriteRender>(0);
	m_spr->Init(
		L"sprite/title.dds",
		GraphicsEngine().Get2DSpaceScreenWidth(),
		GraphicsEngine().Get2DSpaceScreenHeight()
	);
	return true;
}
void Title::Update()
{
	switch (m_enStep) {
	case enStep_Disp:
		if (Pad(0).IsPressAnyKey()) {
			m_fade = FindGO<Fade>(GameObjectNames::FADE);
			m_fade->StartFade({ 0.0f, 0.0f, 0.0f, 1.0f }, 0.5f);
			m_enStep = enStep_WaitFade;
		}
		break;
	case enStep_WaitFade:
		if (m_fade->IsFade() == false) {
			NewGO<Game>(0);
			DeleteGO(this);
		}
		break;
	}

}


