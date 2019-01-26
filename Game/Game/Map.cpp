#include "stdafx.h"
#include "Map.h"


namespace {
	/// <summary>
	/// マップのサイズ。
	/// </summary>
	const float MAP_SIZE[GameSettings::GetNumLevel()] = {
		10000.0f,
		20000.0f,
		30000.0f,
		40000.0f,
		50000.0f,
	};
	/// <summary>
	/// マップのグリッド。
	/// </summary>
	const float MAP_GRID_SIZE = 1000.0f;
}
Map::Map()
{
}
Map::~Map()
{
	DeleteGO(m_treeRender);
}
bool Map::Start()
{
	//ステージの難易度に応じて適当に木を生成する。
	auto mapSize = MAP_SIZE[GameSettings::GetLevel()];
	//はやす木の数を決める。
	int numTree_x = mapSize / MAP_GRID_SIZE;
	int numTree_y = numTree_x;
	int numTreeInstance = numTree_x * numTree_y;
	//木の
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
	for (auto& symbolTreeRender : m_symboleTreeRender){
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
		}
	}
	return true;
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