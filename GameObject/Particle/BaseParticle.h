#pragma once
#include <cassert>
#include "math/MyMath.h"
#include "../enum/MyEnum.h"
#include "../const/MyConst.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "ImGui.h"

/// <summary>
/// 全てのパーティクルの大元になるクラス
/// </summary>
class BaseParticle {
public: // メンバ関数

	/// <summary>
	/// パーティクル共通の初期化関数
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// パーティクル固有の初期化関数
	/// </summary>
	virtual void SuccessorInitialize();

	/// <summary>
	/// パーティクル共通の更新処理
	/// </summary>
	virtual void Update();
	/// <summary>
	/// パーティクル固有の更新関数
	/// </summary>
	virtual void SuccessorUpdate();

	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	virtual void Draw(ViewProjection viewProjection);

	#pragma region アクセッサ等

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns>ワールドトランスフォーム</returns>
	WorldTransform GetWorldTransform() { return worldTransform_; }

	/// <summary>
	/// 位置座標のセッター
	/// </summary>
	/// <param name="translation">設定する位置座標</param>
	void SetTranslation(Vector3 translation) { worldTransform_.translation_ = translation; }

	/// <summary>
	/// パーティクルの有効状態をセットするセッター
	/// </summary>
	/// <param name="isAlive">有効にするか否か</param>
	void SetIsAlive(int32_t isAlive) { isAlive_ = isAlive; }
	/// <summary>
	/// パーティクルの有効状態のゲッター
	/// </summary>
	int32_t GetIsAlive() { return isAlive_; }

	/// <summary>
	/// パーティクルの終了状態をセットするセッター
	/// </summary>
	/// <param name="isEnd">終了するか</param>
	void SetIsEnd(int32_t isEnd) { isEnd_ = isEnd; }
	/// <summary>
	/// パーティクルの終了状態を取得するゲッター
	/// </summary>
	/// <returns>終了状態</returns>
	int32_t GetIsEnd() { return isEnd_; }

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
	/// パーティクルのタイプを取得するゲッター
	/// </summary>
	/// <returns>パーティクルタイプ</returns>
	virtual ParticleType GetType() { return ParticleDefault; }

	/// <summary>
	/// パーティクルの属するオブジェクトのタグのゲッター
	/// </summary>
	/// <returns>パーティクルの属するオブジェクトのタグ</returns>
	virtual ObjectTag GetTag() { return tag_; }
	/// <summary>
	/// パーティクルの属するオブジェクトのタグのセッター
	/// </summary>
	/// <param name="tag">セットするタグ</param>
	void SetTag(ObjectTag tag) { tag_ = tag; }

#pragma endregion

	#pragma region その他関数群

	/// <summary>
	/// 実際に値を加算する前に呼び出すことで速度の影響を受けるようにする関数
	/// </summary>
	virtual void InfluenceTimeScale();

#pragma endregion

protected: // メンバ変数

	// パーティクルの速度
	float timeScale_;
	// パーティクル固有の速度を有効にするか
	int32_t enableMyTimeScale_;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	// エフェクトの有効か非有効か
	int32_t isAlive_;
	// エフェクトの終了状態
	int32_t isEnd_;

	// エフェクトの属するオブジェクトタグ
	ObjectTag tag_;

};
