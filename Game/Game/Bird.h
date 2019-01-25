#pragma once
class Bird : public IGameObject
{
public:
	Bird();
	~Bird();
	bool Start() override;
	void Update() override;
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
};

