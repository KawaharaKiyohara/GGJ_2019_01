#include "stdafx.h"
#include "Map.h"


namespace {
	
	/// <summary>
	/// マップのグリッド。
	/// </summary>
	const float MAP_GRID_SIZE = 1000.0f;
	/// <summary>
	/// 木の半径。
	/// </summary>
	const float TREE_RADIUS = 130.0f;
	const float TREE_HEIGHT = 500.0f;
}
Map::Map()
{
}
Map::~Map()
{
	DeleteGO(m_treeRender);
	DeleteGO(m_groundRender);
	for (auto& symbolTreeRender : m_symboleTreeRender) {
		DeleteGO(symbolTreeRender);
	}
	DeleteGO(m_nestRender);
}
bool Map::Start()
{
	//地面を初期化する、。
	InitGround();
	//木を初期化する。
	InitTree();
	//巣を作成。
	InitNest();
	return true;
}
void Map::InitNest()
{
	m_nestRender = NewGO<prefab::CSkinModelRender>(0);
	m_nestRender->Init(CmoFilePaths::NEST);
	m_nestRender->SetShadowCasterFlag(true);
	m_nestRender->SetShadowReceiverFlag(true);
	//巣の座標をランダムで決める。
	int index = Random().GetRandInt() % m_allTreeInstancingData.size();
	auto& instancingData = m_allTreeInstancingData[index];
	auto pos = instancingData.pos;
	pos.y += 2500.0f;
	pos.z += 300.0f;
	m_nestRender->SetPosition(pos);
	CVector3 emissionColor = { 0.5764705882352941f, 0.32421875f, 0.16015625f };
	emissionColor *= 20.0f;
	m_nestRender->SetEmissionColor(emissionColor);
	m_nestRender->SetScale({ 3.0f, 3.0f, 3.0f });
	GameSettings::SetGoalPosition(pos);
}

void Map::InitGround()
{
	m_specMap.CreateFromDDSTextureFromFile(L"modelData/bg/bgSpec.dds");
	//地面を作成。
	m_groundRender = NewGO<prefab::CSkinModelRender>(0);
	m_groundRender->Init(CmoFilePaths::GROUND);
	m_groundRender->SetShadowReceiverFlag(true);
	m_groundRender->FindMaterial([&](CModelEffect* mat) {
		mat->SetSpecularMap(m_specMap);
	});
}

void Map::InitTree()
{
	//ステージの難易度に応じて適当に木を生成する。
	auto mapSize = GameSettings::GetMapSize();
	//はやす木の数を決める。
	int numTree_x = mapSize / MAP_GRID_SIZE;
	int numTree_y = numTree_x;
	int numTreeInstance = numTree_x * numTree_y;
	//木のインスタンシングデータ用のメモリを確保するぜ。
	m_allTreeInstancingData.resize(numTreeInstance);

	//木はインスタンシング描画だっぜ。
	m_treeRender = NewGO<prefab::CSkinModelRender>(0);
	m_treeRender->Init(CmoFilePaths::TREE, nullptr, 0, enFbxUpAxisZ, numTreeInstance);
	m_treeRender->SetShadowCasterFlag(true);
	m_treeRender->SetShadowReceiverFlag(true);
	const wchar_t* symbolTreeFilePaths[] = {
		CmoFilePaths::SINBOL_TREE_RED,
		CmoFilePaths::SINBOL_TREE_BLUE,
		CmoFilePaths::SINBOL_TREE_GREEN,
		CmoFilePaths::SINBOL_TREE_YELLOW,
		CmoFilePaths::SINBOL_TREE_PURPLE,

	};
	int symbolNo = 0;
	for (auto& symbolTreeRender : m_symboleTreeRender) {
		symbolTreeRender = NewGO<prefab::CSkinModelRender>(0);
		symbolTreeRender->Init(symbolTreeFilePaths[symbolNo], nullptr, 0, enFbxUpAxisZ, numTreeInstance);
		symbolTreeRender->SetShadowCasterFlag(true);
		symbolTreeRender->SetShadowReceiverFlag(true);
		symbolNo++;
	}


	for (int x = 0; x < numTree_x; x++) {
		for (int y = 0; y < numTree_y; y++) {
			int t = Random().GetRandInt() % 100;
			int index = y * numTree_x + x;
			auto& instancingData = m_allTreeInstancingData[index];
			if (t < 10) {
				//5%の確率でシンボル木を作成する。
				int symbolNo = Random().GetRandInt() % NUM_SYMBOL_TREE;
				instancingData.skinModelRender = m_symboleTreeRender[symbolNo];
			}
			else {
				//通常木
				instancingData.skinModelRender = m_treeRender;
			}
			instancingData.pos.x = (x % numTree_x) * MAP_GRID_SIZE - mapSize * 0.5f;
			instancingData.pos.y = 0.0f;
			instancingData.pos.z = (y % numTree_y) * MAP_GRID_SIZE - mapSize * 0.5f;
			//ランダムにはやしてみる。
			instancingData.pos.x += CMath::Lerp(Random().GetRandDouble(), MAP_GRID_SIZE * -0.3f, MAP_GRID_SIZE * 0.3f);
			instancingData.pos.z += CMath::Lerp(Random().GetRandDouble(), MAP_GRID_SIZE * -0.3f, MAP_GRID_SIZE * 0.3f);
			instancingData.rot = CQuaternion::Identity;
			instancingData.scale = CVector3::One;
			instancingData.phyStaticObject = std::make_unique<CPhysicsStaticObject>();
			auto capsulePos = instancingData.pos;
			capsulePos.y += TREE_HEIGHT * 0.3f;
			instancingData.phyStaticObject->CreateCapsule(capsulePos, CQuaternion::Identity, TREE_RADIUS, TREE_HEIGHT);
		}
	}
}
void Map::Update()
{
	for (auto& instanceData : m_allTreeInstancingData) {
		instanceData.skinModelRender->UpdateInstancingData(
			instanceData.pos,
			instanceData.rot,
			instanceData.scale);
	}
}