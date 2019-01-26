#pragma once
class Bird;
class HawkGene;
class Hawk;
class AtkHawk : public IGameObject
{
public:
	AtkHawk();
	~AtkHawk();
	bool Start() override;
	void Update() override;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
private:
	CVector3 m_PlayerPos = CVector3::Zero;
	CVector3 m_HawkPos = CVector3::Zero;
	Bird* m_bird = nullptr;
	CVector3 m_oldbirdpos = CVector3::Zero;
	CVector3 m_movespeed = CVector3::Zero;
	enum Enstate {
		enState_Descent,
		enState_Atk,
		enState_return,
	};
	Enstate m_state = enState_Descent;
	HawkGene* m_HawkGene = nullptr;
	Hawk* m_Hawk = nullptr;
	CQuaternion m_rot;
	CVector3 m_muki = CVector3::Zero;
};

