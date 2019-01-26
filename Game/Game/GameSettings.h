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
private:
	static int m_level;			//難易度。
	
};


