#pragma once
/// <summary>
/// 地形生成器
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
	/// 地面を初期化。
	/// </summary>
	void InitGround();
	/// <summary>
	/// 木を初期化。
	/// </summary>
	void InitTree();
	/// <summary>
	/// 巣を初期化する。
	/// </summary>
	void InitNest();
	/// <summary>
	/// 餌を初期化する。
	/// </summary>
	void InitFeed();
private:
	static constexpr int	NUM_SYMBOL_TREE = 5; //シンボルツリーの数。
	prefab::CSkinModelRender* m_treeRender = nullptr; //普通の木のレンダラー。
	std::array<prefab::CSkinModelRender*, NUM_SYMBOL_TREE> m_symboleTreeRender; //シンボルツリーのレンダラー。

	/// <summary>
	/// インスタンシング用のデータ。
	/// </summary>
	struct SInstancingData {
		CVector3 pos;
		CQuaternion rot;
		CVector3 scale;
		prefab::CSkinModelRender* skinModelRender = nullptr;
		std::unique_ptr<CPhysicsStaticObject> phyStaticObject;
	};
	std::vector< SInstancingData> m_allTreeInstancingData;			//全ての木用のインスタンシングデータ。
	prefab::CSkinModelRender* m_groundRender = nullptr;		//スキンモデルレンダラー。
	prefab::CSkinModelRender* m_nestRender = nullptr;		//巣・
	CShaderResourceView m_specMap;
};

