#pragma once
class Feed:public IGameObject
{
public:
	Feed();
	~Feed();
	bool Start();
	void Update();
private:
	CVector3 m_position = CVector3::Zero;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
};

