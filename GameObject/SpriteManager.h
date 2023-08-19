#pragma once
#include <WinApp.h>
#include "../const/MyConst.h"
#include "Sprite/BaseSprite.h"

/// <summary>
/// 全てのスプライトの管理クラス
/// </summary>
class SpriteManager {
private: // コンストラクタ等
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SpriteManager();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SpriteManager();

public: // メンバ関数

	// コピーコンストラクタ無効
	SpriteManager(const SpriteManager& obj) = delete;
	// 代入演算子無効
	SpriteManager& operator=(const SpriteManager& obj) = delete;

	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>クラスのインスタンス</returns>
	static SpriteManager* GetInstance();

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

	#pragma region アクセッサ等

	/// <summary>
	/// 指定したスプライトの速度を取得するゲッター
	/// </summary>
	/// <param name="value">取得したいインデックス</param>
	/// <returns>速度</returns>
	float GetTimeScale(int value) { return sprites_[value]->GetTimeScale(); }
	/// <summary>
	/// 指定したスプライトの速度を設定するセッター
	/// </summary>
	/// <param name="value">設定したいインデックス</param>
	/// <param name="timeScale">設定したい速度</param>
	void SetTimeScale(int value, float timeScale);
	/// <summary>
	/// 指定したタグのスプライトの速度を一斉に変更するセッター
	/// </summary>
	/// <param name="tag">設定したいタグ</param>
	/// <param name="timeScale">設定したい速度</param>
	void SetTimeScale(ObjectTag tag, float timeScale);

	/// <summary>
	/// 指定したスプライトの固有速度の有効非有効を切り替えるセッター
	/// </summary>
	/// <param name="value">切り替えるインデックス</param>
	/// <param name="enable">有効非有効</param>
	void SetEnableMyTimeScale(int value, bool enable) {
		sprites_[value]->SetEnableMyTimeScale(enable);
	}
	/// <summary>
	/// 指定したタグのスプライトの固有速度の有効非有効を一斉に変更するセッター
	/// </summary>
	/// <param name="tag">設定したいタグ</param>
	/// <param name="enable">有効非有効</param>
	void SetEnableMyTimeScale(ObjectTag tag, bool enable);

#pragma endregion

	#pragma region スプライトの生成を行う関数

	

#pragma endregion

	#pragma region その他関数群

	/// <summary>
	/// イージングを用いてスプライトが現在描画するべき画像をセットする関数
	/// </summary>
	/// <param name="sprite">アニメーションさせるスプライト</param>
	/// <param name="t">現在のt</param>
	/// <param name="start">画像配列の始まり</param>
	/// <param name="end">画像配列の終わり</param>
	/// <param name="isLoop">ループさせるか</param>
	int SetSpriteAnimationImage(float &t, int start, int end, bool isLoop);

#pragma endregion


private: // メンバ変数

	// スプライト
	BaseSprite* sprites_[kMaxSpriteCount];

	// レティクルテクスチャ
	uint32_t textureHandleReticle_ = 0u;

	// Imguiでの生成を行うための変数
	Vector2 setTranslate_{};
	float setTimeScale_;
	bool enableMyTimeScale_[kMaxSpriteCount];
	int select_;
	ObjectTag tag_;

};
