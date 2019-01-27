#pragma once

/// <summary>
/// ゲームオブジェクトの名前
/// </summary>

class GameObjectNames {
public:
	/// <summary>
	/// ゲーム
	/// </summary>
	static constexpr char* GAME = "ゲーム";
	/// <summary>
	/// ゲームスタートカット。
	/// </summary>
	static constexpr char* GAME_START_CUT = "ゲームスタートカット";

	static constexpr char* GAME_CLEAR_CUT = "ゲームクリアカット";
	/// <summary>
	/// ディレクションライト
	/// </summary>
	static constexpr char* DIRECTION_LIGHT = "ディレクションライト";
	/// <summary>
	/// 空
	/// </summary>
	static constexpr char* SKY = "空";
	/// <summary>
	/// 鳥
	/// </summary>
	static constexpr char* BIRD = "鳥";
	/// <summary>
	/// 鷹
	/// </summary>
	static constexpr char* HAWK = "鷹";
	/// <summary>
	/// 鷹生成機
	/// </summary>
	static constexpr char* HAWK_GENE = "鷹生成機";
	/// <summary>
	/// 蛇。
	/// </summary>
	static constexpr char* SNAKE = "蛇";
	/// <summary>

	/// 地形。
	/// </summary>
	static constexpr char* MAP = "マップ";

	/// カメラ
	/// </summary>
	static constexpr char* CAMERA = "カメラ";

	/// 餌
	/// </summary>
	static constexpr char* FEED = "餌";
	/// <summary>
	/// フェード
	/// </summary>
	static constexpr char* FADE = "ファード";
};