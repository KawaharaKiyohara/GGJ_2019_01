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
	CVector3 m_scale = { 5.0f,5.0f,5.0f };
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
};

