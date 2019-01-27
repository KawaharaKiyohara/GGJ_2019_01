#pragma once
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
private:
	static int m_level;			//難易度。
	static CVector3 m_startPosition;	//ゲーム開始座標。
	static CVector3 m_goalPosition;		//ゴール座標。
};


