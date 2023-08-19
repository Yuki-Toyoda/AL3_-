#include "BaseObject.h"
#include "../GameObject/BaseManager.h"

void BaseObject::Initialize() {
	// 固有の初期化処理を呼び出す
	SuccessorInitialize();
}

void BaseObject::SuccessorInitialize() {
	
	// ワールドトランスフォーム初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = {-1000.0f, -1000.0f};
	// 当たり判定半径初期化
	radius_ = 0.0f;
	// ゲーム速度初期化
	timeScale_ = BaseManager::GetInstance()->GetTimeScale();
	// 固有の速度を無効
	enableMyTimeScale_ = false;

	// 生存状態を非生存に
	isAlive_ = false;
	
	// タグを設定
	tag_ = TagNone;

}

void BaseObject::Update() { 
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

void BaseObject::SuccessorUpdate() {

}

void BaseObject::Draw(ViewProjection viewProjection) {

}

void BaseObject::OnHit(ObjectType type) {
	switch (type) {
	case TypeNone:
		break;
	case TypePlayer:
		break;
	case TypeEnemy:
		break;
	case TypePlayerBullet:
		break;
	}
}

void BaseObject::InfluenceTimeScale() {}
