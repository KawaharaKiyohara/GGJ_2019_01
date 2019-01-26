#pragma once
class Hawk;
class HawkGene : public IGameObject
{
public:
	HawkGene();
	~HawkGene();
	bool Start() override;
	void Update() override;
private:
	//�e�̂ق�
	Hawk* m_Hawk1 = nullptr;
	//�{��
	Hawk* m_Hawk2 = nullptr;
	//�����܂ł̃J�E���g
	int m_AppearCount = 0;
	//�e���o����ɖ{�̂��P���|����܂ł̃J�E���g
	int m_HitCount = 0;
};

