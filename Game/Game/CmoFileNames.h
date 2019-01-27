#pragma once

/// <summary>
/// CMOファイルのファイルパス。
/// </summary>

class CmoFilePaths {
public:
	/// <summary>
	/// 子供の鳥のcmoファイルのパス。
	/// </summary>
	static constexpr wchar_t* CHILD_BIRD = L"modelData/bird/torikariS.cmo";
	/// <summary>               
	/// 大人の鳥のcmoファイルのパス。
	/// </summary>
	static constexpr wchar_t* BIRD = L"modelData/bird/NfryBird.cmo";
	/// <summary>
	/// 大量生産の木のモデル
	/// </summary>
	static constexpr wchar_t* TREE = L"modelData/tree/ki.cmo";
	/// <summary>
	/// シンボルになる木(赤)のモデル。
	/// </summary>
	static constexpr wchar_t* SINBOL_TREE_RED = L"modelData/tree/symbolTreeRed.cmo";
	static constexpr wchar_t* SINBOL_TREE_BLUE = L"modelData/tree/symbolTreeBlue.cmo";
	static constexpr wchar_t* SINBOL_TREE_GREEN = L"modelData/tree/symbolTreeGreen.cmo";
	static constexpr wchar_t* SINBOL_TREE_YELLOW = L"modelData/tree/symbolTreeYellow.cmo";
	static constexpr wchar_t* SINBOL_TREE_PURPLE = L"modelData/tree/symbolTreePurple.cmo";
	/// <summary>
	/// 鷹のモデル
	/// </summary>
	static constexpr wchar_t* HAWK = L"modelData/hawk/kariwasi.cmo";
	static constexpr wchar_t* HAWKSHADOW = L"modelData/hawk/hawkshadow.cmo";
	/// <summary>
	/// 蛇
	/// </summary>
	static constexpr wchar_t* SNAKE = L"modelData/snake/karihebi.cmo";
	/// <summary>
	/// 巣
	/// </summary>
	static constexpr wchar_t* NEST = L"modelData/nest/karisu.cmo";
	/// <summary>
	/// 地面
	/// </summary>
	static constexpr wchar_t* GROUND = L"modelData/bg/ground.cmo";
	/// <summary>
	/// 餌
	/// </summary>
	static constexpr wchar_t* FEED = L"modelData/feed/apple.cmo";
};