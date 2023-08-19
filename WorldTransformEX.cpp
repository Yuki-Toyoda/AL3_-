#include "WorldTransform.h"

void WorldTransform::UpdateMatrix() {

	// スケール、加点、平行移動を合成して行列を計算する
	matWorld_ = MyMath::MakeAffineMatrix(scale_, rotation_, translation_);
	
	// 親がいる場合親のワールド	行列を乗算する
	if (parent_) {
		matWorld_ = matWorld_ * parent_->matWorld_;
	}
	
	// 定数バッファに転送
	TransferMatrix();

}