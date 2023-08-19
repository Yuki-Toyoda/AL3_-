#pragma once
#include "../math/MyMath.h"

/// <summary>
/// 衝突判定を管理するマネージャ
/// </summary>
class CollisonManager{
public: // メンバ関数

	/// <summary>
	/// 球同士の当たり判定を検証する関数
	/// </summary>
	/// <param name="worldPos1">検証するワールド座標1</param>
	/// <param name="radius1">半径1</param>
	/// <param name="worldPos2">検証するワールド座標2</param>
	/// <param name="radius2">半径2</param>
	/// <returns>衝突しているか</returns>
	static bool IsCollison(
	     Vector3 worldPos1, float radius1, Vector3 worldPos2, float radius2);

};
