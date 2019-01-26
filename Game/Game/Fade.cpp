#include "stdafx.h"
#include "Fade.h"


Fade::Fade()
{
}


Fade::~Fade()
{
	DeleteGO(m_spriteRender);
}

bool Fade::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(
		L"sprite/fade.dds", 
		GraphicsEngine().Get2DSpaceScreenWidth(), 
		GraphicsEngine().Get2DSpaceScreenHeight()
	);
	return true;
}
void Fade::Update()
{
	m_timer += GameTime().GetFrameDeltaTime();
	if (m_timer < m_fadeTime) {
		m_currentColor.x = CMath::Lerp(m_timer / m_fadeTime, m_startColor.x, m_targetColor.x);
		m_currentColor.y = CMath::Lerp(m_timer / m_fadeTime, m_startColor.y, m_targetColor.y);
		m_currentColor.z = CMath::Lerp(m_timer / m_fadeTime, m_startColor.z, m_targetColor.z);
		m_currentColor.w = CMath::Lerp(m_timer / m_fadeTime, m_startColor.w, m_targetColor.w);
		m_spriteRender->SetMulColor(m_currentColor);
	}
	else {
		//‚†‚‚„‚…I‚í‚èB
		m_isFade = false;
		m_currentColor = m_targetColor;
		m_spriteRender->SetMulColor(m_currentColor);
	}
}