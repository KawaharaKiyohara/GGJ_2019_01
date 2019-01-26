#include "stdafx.h"
#include "Title.h"
#include "Game.h"


Title::Title()
{
}

Title::~Title()
{
	DeleteGO(m_text);
}
bool Title::Start()
{
	m_text = NewGO<prefab::CFontRender>(0);
	m_text->SetColor({ 1.0f, 1.0f, 0.0f });
	m_text->SetText(L"‚ ‚¢‚é‚Ñ[‚Î[‚Ç");
	m_text->SetPivot({ 0.5f, 0.5f });
	m_text->SetScale(2.0f);
	return true;
}
void Title::Update()
{
	if (Pad(0).IsPressAnyKey()) {
		NewGO<Game>(0);
		DeleteGO(this);
	}
}


