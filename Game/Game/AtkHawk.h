#pragma once
class AtkHawk : public IGameObject
{
public:
	AtkHawk();
	~AtkHawk();
	bool Start() override;
	void Update() override;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
private:
	CVector3 m_startpos = CVector3::Zero;
};

