#pragma once

#include "tkEngine/camera/tkSpringCamera.h"

class Bird;
class GameClearCut : public IGameObject
{
public:
	GameClearCut();
	~GameClearCut();
	void Update() override;
	bool Start() override;
private:
	enum EnStep {
		enStep_SpringCamera,
		enStep_ClearmoziIn,
		enStep_StageNoWait,
		enStep_effect
	};
	EnStep m_step = enStep_SpringCamera;
	CSpringCamera m_springCamera;
	CVector2 m_ClearFontPosition = { -1000.0f, 200.0f };
	prefab::CFontRender* m_ClearFontRender = nullptr;
	std::unique_ptr<DirectX::SpriteFont > m_ClearNoFont;
	Bird* m_bird = nullptr;
	CVector3 m_ClearPosition = CVector3::Zero;
	CVector3 maepurasu = { 10.0f, 0.0f, 0.0f };
	float m_timer = 0.0f;
};

