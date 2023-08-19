#pragma once
#include <cassert>
#include "math/MyMath.h"
#include "../enum/MyEnum.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "ImGui.h"
#include "Sprite.h"

/// <summary>
/// 全てのスプライトの大元となるクラス
/// </summary>
class BaseSprite {
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
	/// スプライトの描画座標を取得するゲッター
	/// </summary>
	/// <returns>スプライトの描画座標</returns>
	Vector2 GetSpriteTranslate() { return sprite_->GetPosition(); }
	/// <summary>
	/// スプライトの描画座標をセットするセッター
	/// </summary>
	/// <param name="translate"></param>
	void SetSpriteTranslate(Vector2 translate) { sprite_->SetPosition(translate); }

	/// <summary>
	/// スプライトの速度を取得するゲッター
	/// </summary>
	/// <returns>スプライト速度</returns>
	float GetTimeScale() { return timeScale_; }
	/// <summary>
	/// スプライトの速度をセットするセッター
	/// </summary>
	/// <param name="timeScale">セットする速度</param>
	void SetTimeScale(float timeScale) { timeScale_ = timeScale; }

	/// <summary>
	/// スプライト固有の速度が有効になっているかを取得するゲッター
	/// </summary>
	/// <returns>有効になっているか否か</returns>
	bool GetEnableMyTimeScale() { return enableMyTimeScale_; }
	/// <summary>
	/// スプライト固有の速度を有効または非有効にするセッター
	/// </summary>
	/// <param name="enableMyTimeScale">有効にするか否か</param>
	void SetEnableMyTimeScale(bool enableMyTimeScale) { enableMyTimeScale_ = enableMyTimeScale; }

	/// <summary>
	/// スプライトの表示状態のゲッター
	/// </summary>
	/// <returns>スプライトの表示状態</returns>
	bool GetIsAlive() { return isAlive_; }

	/// <summary>
	/// スプライトのタイプを取得するゲッター
	/// </summary>
	/// <returns>オブジェクトタイプ</returns>
	virtual SpriteType GetType() { return SpriteNone; }

	/// <summary>
	/// スプライトのタグを取得するゲッター
	/// </summary>
	/// <returns>オブジェクトタグ</returns>
	virtual ObjectTag GetTag() { return tag_; }
	/// <summary>
	/// スプライトのタグのセッター
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

	// スプライト速度
	float timeScale_;
	// 固有の速度を有効にするか
	int32_t enableMyTimeScale_;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	// スプライト
	std::unique_ptr<Sprite> sprite_;

	// 表示状態
	int32_t isAlive_;

	// スプライトの属するオブジェクトタグ
	ObjectTag tag_;

};
