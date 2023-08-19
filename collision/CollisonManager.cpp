#include "CollisonManager.h"

bool CollisonManager::IsCollison(
    Vector3 worldPos1, float radius1, Vector3 worldPos2, float radius2) {
	// 計算用
	float distance{};

	// 2つの球の中心座標の距離をとる
	distance = MyMath::Length(worldPos1 - worldPos2);

	// 衝突しているか
	if (distance <= radius1 + radius2) {
		// 衝突していたらTrueを返す
		return true;
	}

	// していない場合はFalse
	return false;
}
