#include "BaseManager.h"
#include "ObjectManager.h"
#include "ParticleManager.h"
#include "SpriteManager.h"

#pragma region private
BaseManager::BaseManager() {}

BaseManager::~BaseManager() {}
#pragma endregion

#pragma region public

BaseManager* BaseManager::GetInstance() {
	// 関数内Static変数として宣言
	static BaseManager instance;
	return &instance;
}

void BaseManager::Initialize() {

	// 
	input_ = Input::GetInstance();

	// 一人称カメラのインスタンス生成
	FPSCamera_ = new FPSCamera();
	// 一人称カメラ初期化
	FPSCamera_->Initialize();

	// ビュープロジェクション初期化
	viewProjection_.Initialize();

	// ゲーム速度初期化
	timeScale_ = 1.0f;

	// オブジェクト初期化
	objectManager_ = ObjectManager::GetInstance();
	objectManager_->Initialize();

	// パーティクル初期化
	particleManager_ = ParticleManager::GetInstance();
	particleManager_->Initialize();

	// スプライト初期化
	spriteManager_ = SpriteManager::GetInstance();
	spriteManager_->Initialize();

	// Imguiでの生成を行うための変数
	stagingTime_ = 1.0f;
	setTimeScale_ = 1.0f;
	select_ = 0;
	selectTag_ = TagNone;

}

void BaseManager::Update() {

	// オブジェクト更新処理
	objectManager_->Update();
	// パーティクル更新処理
	particleManager_->Update();
	// スプライト更新処理
	spriteManager_->Update();

	// viewProjection行列の更新と転送
	FPSCamera_->Update();
	// ビュープロジェクションを追従カメラのものに設定する
	viewProjection_ = FPSCamera_->GetViewProjection();
	// 行列を定数バッファに転送
	viewProjection_.TransferMatrix();

}

void BaseManager::Draw() {
	// オブジェクト描画処理
	objectManager_->Draw();
	// パーティクル描画処理
	particleManager_->Draw();
}

void BaseManager::SpriteDraw() {
	// スプライト描画
	spriteManager_->Draw(); 
}

void BaseManager::SetTimeScaleWithTag(ObjectTag tag, float timeScale) {
	// オブジェクトマネージャでタイムスケールを有効にする
	objectManager_->SetTimeScale(tag, timeScale);
	// パーティクルマネージャでタイムスケールを有効にする
	particleManager_->SetTimeScale(tag, timeScale);
	// スプライトマネージャでタイムスケールを有効にする
	spriteManager_->SetTimeScale(tag, timeScale);
}

void BaseManager::SetEnableMyTimeScale(ObjectTag tag, bool enable) {
	// オブジェクトマネージャでタイムスケールの有効非有効を切り替える
	objectManager_->SetEnableMyTimeScale(tag, enable);
	// パーティクルマネージャでタイムスケールの有効非有効を切り替える
	particleManager_->SetEnableMyTimeScale(tag, enable);
	// スプライトマネージャでタイムスケールの有効非有効を切り替える
	spriteManager_->SetEnableMyTimeScale(tag, enable);
}

WorldTransform* BaseManager::GetPlayerWorldTransform() { 
	// プレイヤーのワールドトランスフォームを返す
	return objectManager_->GetPlayerWorldTransform();
}

#pragma endregion


