#pragma once
#include <cassert>
#include <string>
#include "math/MyMath.h"
#include "../enum/MyEnum.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "ImGui.h"

/// <summary>
/// プレイヤーや敵等の大元のオブジェクト
/// </summary>
class BaseObject {
public: // メンバ関数

	/// <summary>
	/// オブジェクト共通の初期化関数
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// オブジェクト固有の初期化関数
	/// </summary>
	virtual void SuccessorInitialize();

	/// <summary>
	/// オブジェクト共通の更新処理
	/// </summary>
	virtual void Update();
	/// <summary>
	/// オブジェクト固有の更新関数
	/// </summary>
	virtual void SuccessorUpdate();

	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	virtual void Draw(ViewProjection viewProjection);

	#pragma region アクセッサ等

	/// <summary>
	/// ワールドトランスフォームのアドレスのゲッター
	/// </summary>
	/// <returns>オブジェクトのワールドトランスフォームのアドレス</returns>
	WorldTransform* GetWorldTransformAddress() { return &worldTransform_; }
	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns>ワールドトランスフォーム</returns>
	WorldTransform GetWorldTransform() { return worldTransform_; }
	
	/// <summary>
	/// 位置座標のセッター
	/// </summary>
	/// <param name="translation">設定する座標</param>
	void SetTranslation(Vector3 translation) { worldTransform_.translation_ = translation; }

	/// <summary>
	/// オブジェクトの当たり判定半径を取得するゲッター
	/// </summary>
	/// <returns>当たり判定半径</returns>
	float GetObjectRadius() { return radius_; }

	/// <summary>
	/// オブジェクトの生存状態ゲッター
	/// </summary>
	/// <returns>生存状態</returns>
	bool GetIsAlive() { return isAlive_; }
	/// <summary>
	/// オブジェクトの生存状態のセッター
	/// </summary>
	/// <param name="isAlive">生存させるか否か</param>
	void SetIsAlive(bool isAlive) { isAlive_ = isAlive; }

	/// <summary>
	/// オブジェクトの速度のゲッター
	/// </summary>
	/// <returns>オブジェクトの速度</returns>
	float GetTimeScale() { return timeScale_; }
	/// <summary>
	/// オブジェクトの速度のセッター
	/// </summary>
	/// <param name="timeScale">設定する速度</param>
	void SetTimeScale(float timeScale) { timeScale_ = timeScale; }

	/// <summary>
	/// オブジェクトの固有の速度が有効になっているかのゲッター
	/// </summary>
	/// <returns>有効になっているか否か</returns>
	bool GetEnableMyTimeScale() { return enableMyTimeScale_; }
	/// <summary>
	/// オブジェクトの固有の速度を有効にするかのセッター
	/// </summary>
	/// <param name="enableMyTimeScale">有効または非有効</param>
	void SetEnableMyTimeScale(bool enableMyTimeScale) { enableMyTimeScale_ = enableMyTimeScale; }

	/// <summary>
	/// オブジェクトのタイプを取得するゲッター
	/// </summary>
	/// <returns>オブジェクトタイプ</returns>
	virtual ObjectType GetType() { return TypeNone; }

	/// <summary>
	/// オブジェクトのタグを取得するゲッター
	/// </summary>
	/// <returns>オブジェクトタグ</returns>
	virtual ObjectTag GetTag() { return tag_; }
	/// <summary>
	/// 指定したタグをセットするセッター
	/// </summary>
	/// <param name="tag"></param>
	void SetTag(ObjectTag tag) { tag_ = tag; }

	/// <summary>
	/// オブジェクトの当たり判定タイプを取得するゲッター
	/// </summary>
	/// <returns>当たり判定タイプ</returns>
	virtual collisionType GetCollison() { return CollisionNone; }

#pragma endregion

#pragma region その他関数群

	/// <summary>
	/// 衝突時衝突マネージャで呼び出す関数
	/// </summary>
	/// <param name="type">衝突したオブジェクトのタイプ</param>
	virtual void OnHit(ObjectType type);

	/// <summary>
	/// 実際に値を加算する前に呼び出すことで速度の影響を受けるようにする関数
	/// </summary>
	virtual void InfluenceTimeScale();

#pragma endregion


protected: // メンバ変数

	// オブジェクトの速度
	float timeScale_;
	// 固有の速度を有効にするか
	int32_t enableMyTimeScale_;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	//当たり判定用半径
	float radius_;
	// 移動ベクトル
	Vector3 move_{};

	// 生存状態
	int32_t isAlive_;

	// オブジェクトのタグ
	ObjectTag tag_;

};
