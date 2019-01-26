#include "stdafx.h"
#include "Timer.h"
#include "tkEngine/graphics/font/tkFontRender.h"

Timer::Timer()
{
}
Timer::~Timer()
{
	DeleteGO(m_cfontrender);
}
bool Timer::Start() {

	m_cfontrender = NewGO<prefab::CFontRender>(0);
	m_cfontrender->SetText(L"‚±‚ñ‚É‚¿‚Í");

	/*m_cfontrender->SetFont(font);
	m_cfontrender->SetText(text1);
	m_cfontrender->SetPosition({ 1.0f,1.0f });*/


	return true;
}

void Timer::Update() {

	
	m_cfontrender->SetPosition(pos);

}