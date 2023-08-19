#include "BaseSprite.h"
#include "../BaseManager.h"

void BaseSprite::Initialize() {
	// 固有の初期化処理を呼び出す
	SuccessorInitialize();
}

void BaseSprite::SuccessorInitialize() {

	// ゲーム速度初期化
	timeScale_ = BaseManager::GetInstance()->GetTimeScale();
	// 固有の速度を無効
	enableMyTimeScale_ = false;

	// ワールドトランスフォーム初期化
	worldTransform_.Initialize();

	// 表示しない
	isAlive_ = false;

	// タグを設定
	tag_ = TagNone;
}

void BaseSprite::Update() {
	// 固有の速度が有効でなければ
	if (!enableMyTimeScale_) {
		// 全体のゲーム速度を取得
		timeScale_ = BaseManager::GetInstance()->GetTimeScale();
	}

	// 固有の更新処理を呼び出す
	SuccessorUpdate();
	// 行列の更新、転送を行う
	worldTransform_.UpdateMatrix();
}

void BaseSprite::SuccessorUpdate() {
	
}

void BaseSprite::Draw(ViewProjection viewProjection) {

}

void BaseSprite::InfluenceTimeScale() {}
