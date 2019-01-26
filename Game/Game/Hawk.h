#pragma once
class Bird;
class AtkHawk;
/// <summary>
/// ��
/// </summary>
class Hawk : public IGameObject
{
public:
	Hawk();
	~Hawk();
	bool Start() override;
	void Update() override;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_PlayerPos = CVector3::Zero;
private:
	
	CVector3 m_ShadowPos = {-400.0f, 350.0f, 0.0f};
	Bird* m_bird = nullptr;
	AtkHawk* m_AtkHawk = nullptr;
	int kierucount = 0;
};

