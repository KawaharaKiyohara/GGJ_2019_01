#pragma once

//蛇の生成率。値を大きくすると蛇が増える。デフォルト0.01
static const float SNAKE_GEN_RATE = 0.012f;

//餌の生成率。値を大きすると餌が増える。デフォルト0.01
static const float FEED_GEN_RATE = 0.016f;

//鳥が成長するために必要な餌の数。
static const float GROWUP_FEED_COUNT = 6;

//鳥の移動速度(地面にいるとき)
static const float BIRD_MOVE_SPEED = 200.0f;

//鳥の移動速度(飛んでいるとき)
//80.0fの方を変更するとよいです。
static const float BIRD_FLY_MOVE_SPEED = 220.0f * 180.0f;

/// <summary>
/// ゲームの設定クラス。
/// </summary>
class GameSettings
{
private:
	GameSettings();
public:
	~GameSettings();
	
	/// <summary>
	/// ゲームの難易度を取得
	/// </summary>
	/// <returns></returns>
	static int GetLevel() 
	{
		return m_level;
	}
	/// <summary>
	/// 難易度を設定する。
	/// </summary>
	/// <param name="level">難易度</param>
	static void SetLevel(int level)
	{
		m_level = level;
	}
	/// <summary>
	/// 難易度の数を取得する。
	/// </summary>
	/// <returns></returns>
	static constexpr int GetNumLevel()
	{
		return 5;
	}
	/// <summary>
	/// マップのサイズを取得。
	/// </summary>
	/// <returns></returns>
	static float GetMapSize() 
	{
		const float MAP_SIZE[GameSettings::GetNumLevel()] = {
			//ここを書き換えたら最終ステージの設定になる
			10000.0f,
			12500.0f,
			15000.0f,
			17500.0f,
			50000.0f,
		};
		return MAP_SIZE[GetLevel()];
	}
	static void SetStartPosition(CVector3 pos)
	{
		m_startPosition = pos;
	}
	/// <summary>
	/// ゲーム開始座標取得。
	/// </summary>
	/// <returns></returns>
	static CVector3 GetStartPosition()
	{
		return m_startPosition;
	}
	/// <summary>
	/// ゴール座標。
	/// </summary>
	/// <returns></returns>
	static CVector3 GetGoalPosition()
	{
		return m_goalPosition;
	}
	/// <summary>
	/// ゴールの座標を設定する。
	/// </summary>
	/// <param name="pos"></param>
	static void SetGoalPosition(CVector3 pos)
	{
		m_goalPosition = pos;
	}
	/// <summary>
	/// シャドウマップのライトのインゲーム中の高さを取得。
	/// </summary>
	/// <returns></returns>
	static float GetShadowMapLightHeightInGame()
	{
		return UnitM(15.0f);
	}
	/// <summary>
	/// スタートカットの時のシャドウマップのライトの高さを取得。
	/// </summary>
	/// <returns></returns>
	static float GetShadowMapLightHeightInStartCut()
	{
		return UnitM(60.0f);
	}
private:
	static int m_level;			//難易度。
	static CVector3 m_startPosition;	//ゲーム開始座標。
	static CVector3 m_goalPosition;		//ゴール座標。
};


