#pragma once

class Fade;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	void Update() override;
	bool Start() override;
private:
	enum EnStep {
		enStep_Disp,
		enStep_WaitFade
	};
	Fade* m_fade = nullptr;
	EnStep m_enStep = enStep_Disp;
	prefab::CSpriteRender* m_spr = nullptr;
};


