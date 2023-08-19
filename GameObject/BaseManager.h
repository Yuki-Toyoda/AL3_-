#pragma once
#include "../enum/MyEnum.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "../Camera/FPSCamera.h"

// クラスの前方宣言
class ObjectManager;
class ParticleManager;
class SpriteManager;

/// <summary>
/// オブジェクト、3Dパーティクル、スプライト全てを管理するクラス
/// </summary>
class BaseManager final{
private: // コンストラクタ等

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BaseManager();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~BaseManager();

public: // メンバ関数

	// コピーコンストラクタ無効
	BaseManager(const BaseManager& obj) = delete;
	// 代入演算子無効
	BaseManager& operator=(const BaseManager& obj) = delete;

	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>クラスのインスタンス</returns>
	static BaseManager* GetInstance();

	/// <summary>
	/// 初期化関数
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();

	/// <summary>
	/// スプライトの描画関数
	/// </summary>
	void SpriteDraw();

	#pragma region アクセッサ等

	/// <summary>
	/// ビュープロジェクションのアドレスを返すゲッター
	/// </summary>
	/// <returns>ビュープロジェクションアドレス</returns>
	ViewProjection* GetViewProjectionAdress() { return &viewProjection_; }
	/// <summary>
	/// ビュープロジェクションのゲッター
	/// </summary>
	/// <returns>ビュープロジェクション</returns>
	ViewProjection GetViewProjection() const { return viewProjection_; }
	/// <summary>
	/// ビュープロジェクションセッター
	/// </summary>
	/// <param name="viewProjection">セットするビュープロジェクション</param>
	void SetViewProjection(const ViewProjection& viewProjection) {
		viewProjection_ = viewProjection;
	};

	/// <summary>
	/// タイムスケールを取得するゲッター
	/// </summary>
	/// <returns>現在のゲーム全体の速度</returns>
	float GetTimeScale() const { return timeScale_; };
	/// <summary>
	/// タイムスケールをセットするセッター
	/// </summary>
	/// <param name="timeScale">設定するゲーム速度</param>
	void SetTimeScale(float timeScale) { timeScale_ = timeScale; };

	/// <summary>
	/// タグを基準に全ての速度を一括で変更するセッター
	/// </summary>
	/// <param name="timeScale">設定する速度</param>
	/// <param name="tag">速度を設定するタグ</param>
	void SetTimeScaleWithTag(ObjectTag tag, float timeScale);

	/// <summary>
	/// タグを基準に全ての固有速度の有効非有効を変更するセッター
	/// </summary>
	/// <param name="enable">有効非有効</param>
	/// <param name="tag">有効非有効を切り替えるタグ</param>
	void SetEnableMyTimeScale(ObjectTag tag, bool enable);

	/// <summary>
	/// プレイヤーのワールドトランスフォームを取得する関数
	/// </summary>
	/// <returns>プレイヤーのワールドトランスフォーム</returns>
	WorldTransform* GetPlayerWorldTransform();

	/// <summary>
	/// カメラのシェイク値を設定するセッター
	/// </summary>
	/// <param name="Vec">シェイク値</param>
	void SetCameraShake(Vector2 Vec) { FPSCamera_->SetShakeVec(Vec); }

#pragma endregion

	#pragma region 演出関数

	

#pragma endregion


private: // メンバ変数

	Input* input_ = nullptr;

	// 一人称カメラ
	FPSCamera* FPSCamera_ = nullptr;

	// 全体ゲーム速度
	float timeScale_;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	// オブジェクトマネージャー
	ObjectManager* objectManager_ = nullptr;
	// パーティクルマネージャー
	ParticleManager* particleManager_ = nullptr;
	// スプライトマネージャ
	SpriteManager* spriteManager_ = nullptr;

	#pragma region 演出用変数

	

#pragma endregion

	// Imguiでの生成を行うための変数
	float stagingTime_;
	float setTimeScale_;
	int select_;
	ObjectTag selectTag_;

};
