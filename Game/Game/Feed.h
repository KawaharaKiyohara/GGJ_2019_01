#pragma once
class Feed:public IGameObject
{
public:
	Feed();
	~Feed();
	bool Start();
	void Update();
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition() const
	{
		return m_position;
	}
private:
	CVector3 m_position = {0.0f,0.0f,500.0f};
	CVector3 m_scale = { 2.0f,2.0f,2.0f };
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	float m_timer = 0.0f;
	float m_timer2 = 0.0f;
	float m_time = 20.0f;
	float m_time2 = 10.0f;
};

