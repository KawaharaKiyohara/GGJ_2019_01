#pragma once
#include "tkEngine/graphics/font/tkFont.h"
class Timer : public IGameObject
{
public:
	Timer();
	~Timer();
	bool Start();
	void Update();
	prefab::CFontRender* m_cfontrender = nullptr;
	
	
	DirectX::SpriteFont* font;
	CFont m_fontTest;
	CFont m_font;
	CVector2 pos = CVector2::Zero;
	wchar_t text[256];
	std::wstring m_text;
	const wchar_t* text1;
	int timer = 0;
	float m_timer = 0.0f;
	float m_waitTimer;
};

