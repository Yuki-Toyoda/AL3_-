#pragma once
#include "../const/MyConst.h"
#include "../enum/MyEnum.h"
#include "Object/BaseObject.h"
#include "../collision/CollisonManager.h"

/// <summary>
/// 全てのオブジェクトの管理クラス
/// </summary>
class ObjectManager final{
private:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ObjectManager();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ObjectManager();

public: // メンバ関数

	// コピーコンストラクタ無効
	ObjectManager(const ObjectManager& obj) = delete;
	// 代入演算子無効
	ObjectManager& operator=(const ObjectManager& obj) = delete;

	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>クラスのインスタンス</returns>
	static ObjectManager* GetInstance();

	/// <summary>
	/// 全てのオブジェクトの初期化関数
	/// </summary>
	void Initialize();

	/// <summary>
	/// 全てのオブジェクトの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 全てのオブジェクトの描画関数
	/// </summary>
	void Draw();

	#pragma region アクセッサ等

	/// <summary>
	/// プレイヤーのワールドトランスフォームを取得する関数
	/// </summary>
	/// <returns>プレイヤーのワールドトランスフォーム</returns>
	WorldTransform* GetPlayerWorldTransform();

	/// <summary>
	/// 現在のワールド座標のゲッター
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <returns></returns>
	Vector3 GetWorldPos(WorldTransform* worldTransform);

	/// <summary>
	/// 指定したオブジェクトの速度を取得するゲッター
	/// </summary>
	/// <param name="value">取得したいインデックス</param>
	/// <returns>速度</returns>
	float GetTimeScale(int value) { return objects_[value]->GetTimeScale(); }
	/// <summary>
	/// 指定したオブジェクトの速度を設定するセッター
	/// </summary>
	/// <param name="value">設定したいインデックス</param>
	/// <param name="timeScale">設定したい速度</param>
	void SetTimeScale(int value, float timeScale);
	/// <summary>
	/// 指定したタグのオブジェクトの速度を一斉に変更するセッター
	/// </summary>
	/// <param name="tag">設定したいタグ</param>
	/// <param name="timeScale">設定したい速度</param>
	void SetTimeScale(ObjectTag tag, float timeScale);

	/// <summary>
	/// 指定したオブジェクトの固有速度の有効非有効を切り替えるセッター
	/// </summary>
	/// <param name="value">切り替えるインデックス</param>
	/// <param name="enable">有効非有効</param>
	void SetEnableMyTimeScale(int value, bool enable) {
		objects_[value]->SetEnableMyTimeScale(enable);
	}
	/// <summary>
	/// 指定したタグのオブジェクトの固有速度の有効非有効を一斉に変更するセッター
	/// </summary>
	/// <param name="tag">設定したいタグ</param>
	/// <param name="enable">有効非有効</param>
	void SetEnableMyTimeScale(ObjectTag tag, bool enable);

#pragma endregion


	#pragma region オブジェクトの生成を行う関数

	

#pragma endregion

	#pragma region 衝突判定検証関数

	/// <summary>
	/// 引数で指定したオブジェクトとその他のオブジェクトとの当たり判定を検証する関数
	/// </summary>
	void CheckCollision(BaseObject* object);

#pragma endregion


private: // メンバ変数

	// オブジェクト
	BaseObject* objects_[kMaxAliveObjects];

	// Imguiでの生成を行うための変数
	Vector3 spawnTranslate_{};
	Vector3 setTranslate_{};
	float setTimeScale_;
	bool enableMyTimeScale_[kMaxAliveObjects];
	int select_;
	ObjectTag tag_;

};
