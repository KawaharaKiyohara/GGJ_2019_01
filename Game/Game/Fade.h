#pragma once
class Fade : public IGameObject
{
public:
	Fade();
	~Fade();

	//void Update() override;
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;	//スプライトレンダラー。
};

