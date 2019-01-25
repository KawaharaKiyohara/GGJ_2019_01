#pragma once
class Snake : public IGameObject
{
public:
	Snake();
	~Snake();
	bool Start() override;
	void Update() override;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
};

