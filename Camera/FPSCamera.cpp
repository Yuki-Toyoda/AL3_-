#include "FPSCamera.h"

void FPSCamera::Initialize() {
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	shake_ = {0.0f, 0.0f};
	offset_ = {0.0f, 0.0f, 0.0f};
}

void FPSCamera::Update() {

	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		// 旋回速度
		const float speed = 0.025f;

		// スティックの横移動に対してカメラを旋回
		viewProjection_.rotation_.x -= (float)joyState.Gamepad.sThumbRY / SHRT_MAX * speed;
		viewProjection_.rotation_.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * speed;

		// 角度制限
		if (viewProjection_.rotation_.x <= -1.50f) {
			viewProjection_.rotation_.x = -1.50f;
		} else if (viewProjection_.rotation_.x >= 1.50f) {
			viewProjection_.rotation_.x = 1.50f;
		}

#ifdef _DEBUG

		ImGui::Begin("camera");
		ImGui::DragFloat3("move", &viewProjection_.rotation_.x, 0.05f);
		ImGui::End();

#endif // _DEBUG
	}

	// 追従対象が存在すれば
	if (target_) {

		// 追従対象からカメラまでのオフセットを設定
		Vector3 offset = {0.0f, 0.0f, -3.0f};
		offset_ = offset;
		offset_.x += shake_.x;
		offset_.y += shake_.y;

		// カメラの角度から回転行列を生成
		Matrix4x4 rotateMat = MyMath::MakeRotateXYZMatrix(viewProjection_.rotation_);

		// オフセットをカメラの回転に合わせて回転させる
		offset_ = MyMath::Transform(offset_, rotateMat);

		// 座標コピーからオフセット分ずらす
		viewProjection_.translation_ = target_->translation_ + offset_;

	}

	// ビュープロジェクション行列の
	viewProjection_.UpdateMatrix();   // 更新
}
