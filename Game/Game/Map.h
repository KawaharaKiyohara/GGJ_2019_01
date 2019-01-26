#pragma once
/// <summary>
/// �n�`������
/// </summary>
class Map : public IGameObject
{
public:
	Map();
	~Map();
	bool Start() override;
	void Update() override;
private:
	/// <summary>
	/// �n�ʂ��������B
	/// </summary>
	void InitGround();
	/// <summary>
	/// �؂��������B
	/// </summary>
	void InitTree();
	/// <summary>
	/// ��������������B
	/// </summary>
	void InitNest();
	/// <summary>
	/// �a������������B
	/// </summary>
	void InitFeed();
private:
	static constexpr int	NUM_SYMBOL_TREE = 5; //�V���{���c���[�̐��B
	prefab::CSkinModelRender* m_treeRender = nullptr; //���ʂ̖؂̃����_���[�B
	std::array<prefab::CSkinModelRender*, NUM_SYMBOL_TREE> m_symboleTreeRender; //�V���{���c���[�̃����_���[�B

	/// <summary>
	/// �C���X�^���V���O�p�̃f�[�^�B
	/// </summary>
	struct SInstancingData {
		CVector3 pos;
		CQuaternion rot;
		CVector3 scale;
		prefab::CSkinModelRender* skinModelRender = nullptr;
		std::unique_ptr<CPhysicsStaticObject> phyStaticObject;
	};
	std::vector< SInstancingData> m_allTreeInstancingData;			//�S�Ă̖ؗp�̃C���X�^���V���O�f�[�^�B
	prefab::CSkinModelRender* m_groundRender = nullptr;		//�X�L�����f�������_���[�B
	prefab::CSkinModelRender* m_nestRender = nullptr;		//���E
	CShaderResourceView m_specMap;
};

