#pragma once
class Hawk;
class AtkHawk;
class HawkGene : public IGameObject
{
public:
	HawkGene();
	~HawkGene();
	bool Start() override;
	void Update() override;
private:
	//影のほう
	Hawk* m_Hawk1 = nullptr;
	//本体
	AtkHawk* m_Hawk2 = nullptr;
	//現れるまでのカウント
	int m_AppearCount = 0;
	//影が出た後に本体が襲い掛かるまでのカウント
	int m_HitCount = 0;
};

