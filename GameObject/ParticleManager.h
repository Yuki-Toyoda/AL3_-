#pragma once
#include "../const/MyConst.h"
#include "../enum/MyEnum.h"
#include "Particle/BaseParticle.h"

/// <summary>
/// 全てのパーティクルを管理するクラス
/// </summary>
class ParticleManager final {
private: // コンストラクタ等

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParticleManager();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParticleManager();

public: // メンバ関数

	// コピーコンストラクタ無効
	ParticleManager(const ParticleManager& obj) = delete;
	// 代入演算子無効
	ParticleManager& operator=(const ParticleManager& obj) = delete;

	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>クラスのインスタンス</returns>
	static ParticleManager* GetInstance();

	/// <summary>
	/// 全てのパーティクルの初期化関数
	/// </summary>
	void Initialize();

	/// <summary>
	/// 全てのパーティクルの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 全てのパーティクルの描画関数
	/// </summary>
	void Draw();

	#pragma region アクセッサ等

	/// <summary>
	/// 指定したパーティクルの速度を取得するゲッター
	/// </summary>
	/// <param name="value">取得したいインデックス</param>
	/// <returns>速度</returns>
	float GetTimeScale(int value) { return particles_[value]->GetTimeScale(); }
	/// <summary>
	/// 指定したパーティクルの速度を設定するセッター
	/// </summary>
	/// <param name="value">設定したいインデックス</param>
	/// <param name="timeScale">設定したい速度</param>
	void SetTimeScale(int value, float timeScale);
	/// <summary>
	/// 指定したタグのパーティクルの速度を一斉に変更するセッター
	/// </summary>
	/// <param name="tag">設定したいタグ</param>
	/// <param name="timeScale">設定したい速度</param>
	void SetTimeScale(ObjectTag tag, float timeScale);

	/// <summary>
	/// 指定したパーティクルの固有速度の有効非有効を切り替えるセッター
	/// </summary>
	/// <param name="value">切り替えるインデックス</param>
	/// <param name="enable">有効非有効</param>
	void SetEnableMyTimeScale(int value, bool enable) {
		particles_[value]->SetEnableMyTimeScale(enable);
	}
	/// <summary>
	/// 指定したタグのパーティクルの固有速度の有効非有効を一斉に変更するセッター
	/// </summary>
	/// <param name="tag">設定したいタグ</param>
	/// <param name="enable">有効非有効</param>
	void SetEnableMyTimeScale(ObjectTag tag, bool enable);

#pragma endregion

	#pragma region パーティクルの生成を行う関数

	

#pragma endregion


#pragma region その他関数群

#pragma endregion

private: // メンバ変数

	BaseParticle* particles_[kMaxAliveParticle];

	// Imguiでの生成を行うための変数
	Vector3 spawnTranslate_{};
	Vector3 setTranslate_{};
	float setTimeScale_;
	bool enableMyTimeScale_[kMaxAliveParticle];
	bool stilContinuation_[kMaxAliveParticle];
	bool isEnd_[kMaxAliveParticle];
	int select_;
	ObjectTag tag_;

};
