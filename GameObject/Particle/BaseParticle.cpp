#include "BaseParticle.h"
#include "../BaseManager.h"

void BaseParticle::Initialize() {
	// 固有の初期化関数を呼び出す
	SuccessorInitialize();
}

void BaseParticle::SuccessorInitialize() {
	// ワールドトランスフォーム初期化
	worldTransform_.Initialize();
	// 速度リセット
	timeScale_ = BaseManager::GetInstance()->GetTimeScale();
	// 固有の速度を無効化
	enableMyTimeScale_ = false;
	// エフェクトを非有効に
	isAlive_ = false;
	// エフェクトを終了状態に
	isEnd_ = true;
	// エフェクトのタグをデフォルトに
	tag_ = TagNone;
}

void BaseParticle::Update() {
	// 固有の速度が有効でなければ
	if (!enableMyTimeScale_) {
		// 全体のゲーム速度を取得
		timeScale_ = BaseManager::GetInstance()->GetTimeScale();
	}

	// 固有の更新処理を呼び出す
	SuccessorUpdate();
	// ワールド行列の更新と転送
	worldTransform_.UpdateMatrix();
}

void BaseParticle::SuccessorUpdate() {

}

void BaseParticle::Draw(ViewProjection viewProjection) {

}

void BaseParticle::InfluenceTimeScale() {}
