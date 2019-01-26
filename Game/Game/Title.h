#pragma once
class Title : public IGameObject
{
public:
	Title();
	~Title();
	void Update() override;
	bool Start() override;
};

