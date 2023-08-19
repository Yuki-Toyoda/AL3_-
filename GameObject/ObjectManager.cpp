#include "ObjectManager.h"
#include "BaseManager.h"

ObjectManager::ObjectManager() {}

ObjectManager::~ObjectManager() {
	// オブジェクトをリリース
	for (int i = 0; i < kMaxAliveObjects; i++) {
		delete objects_[i];
	}
}

ObjectManager* ObjectManager::GetInstance() {
	// 関数内Static変数として宣言
	static ObjectManager instance;
	return &instance;
}

void ObjectManager::Initialize() {

	// 全てのオブジェクトを初期化する
	for (int i = 0; i < kMaxAliveObjects; i++) {
		objects_[i] = new BaseObject();
		objects_[i]->Initialize();

		// Imguiでの生成を行うための変数の初期化
		enableMyTimeScale_[i] = false;
	}

	// Imguiでの生成を行うための変数の初期化
	spawnTranslate_ = {0.0f, 5.0f, 0.0f};
	setTranslate_ = {0.0f, 5.0f, 0.0f};
	setTimeScale_ = 1.0f;
	select_ = TagNone;
	tag_ = TagNone;
}

void ObjectManager::Update() {

	// オブジェクトのデバック表示
	ImGui::Begin("Objects");

	// セットする際の値を設定
	ImGui::DragFloat3("setTranslate", &setTranslate_.x, 0.05f);
	ImGui::DragFloat("setTImeScale", &setTimeScale_, 0.01f, kMinTimeScale, kMaxTimeScale);
	// 有効タグを調べる
	ImGui::RadioButton("TagNone", &select_, TagNone);
	ImGui::SameLine();
	ImGui::RadioButton("TagPlayer", &select_, TagPlayer);
	ImGui::SameLine();
	ImGui::RadioButton("TagEnemy", &select_, TagEnemy);

	// 全てのオブジェクトの更新関数を呼び出す
	for (int i = 0; i < kMaxAliveObjects; i++) {
		if (objects_[i]->GetType() != TypeNone) {
			objects_[i]->Update();
		}

		// Imguiで敵の座標などを表示、設定する
		if (objects_[i]->GetIsAlive() && objects_[i]->GetType() != TypeNone) {

			char tree[16] = "";
			sprintf_s(tree, "Object%d", i);

			if (ImGui::TreeNode(tree)) {

				// オブジェクトの現在座標を取得
				Vector3 translate = objects_[i]->GetWorldTransform().translation_;
				// Imguiで表示
				ImGui::DragFloat3("translate", &translate.x, 0.05f);
				// 改行しない
				ImGui::SameLine();
				// セットボタンを押すと座標をセットする
				if (ImGui::Button("SetTranslate")) {
					objects_[i]->SetTranslation(setTranslate_);
				}

				// オブジェクトのタイムスケールを取得
				float timeScale = objects_[i]->GetTimeScale();
				// Imguiで表示
				ImGui::DragFloat("timeScale", &timeScale, 0.05f);
				// 改行しない
				ImGui::SameLine();
				// セットボタンを押すと座標をセットする
				if (ImGui::Button("SetTimeScale")) {
					objects_[i]->SetTimeScale(setTimeScale_);
				}

				// チェックボックスによって生存状態の切り替え
				if (objects_[i]->GetType() != TypePlayer) {
					if (ImGui::Button("isAlive")) {
						objects_[i]->SetIsAlive(false);
					}
				}
				

				// 現在のタグを取得
				ObjectTag selectTag = objects_[i]->GetTag();
				switch (selectTag) {
				case TagNone:
					ImGui::Text("NowTag : None");
					break;
				case TagPlayer:
					ImGui::Text("NowTag : Player");
					break;
				case TagEnemy:
					ImGui::Text("NowTag : Enemy");
					break;
				}
				// 改行しない
				ImGui::SameLine();
				// セットボタンを押すとタグをセットする
				if (ImGui::Button("SetTag")) {
					objects_[i]->SetTag((ObjectTag)select_);
				}

				ImGui::TreePop();
			}
		}
	}

	ImGui::End();
}

void ObjectManager::Draw() {

	// 全てのオブジェクトの描画関数を呼び出す
	for (int i = 0; i < kMaxAliveObjects; i++) {
		if (objects_[i]->GetType() != TypeNone) {
			objects_[i]->Draw(BaseManager::GetInstance()->GetViewProjection());
		}
	}
}

WorldTransform* ObjectManager::GetPlayerWorldTransform() {
	// 全てのオブジェクトからプレイヤーを取得する
	for (int i = 0; i < kMaxAliveObjects; i++) {
		if (objects_[i]->GetType() == TypePlayer) {
			return objects_[i]->GetWorldTransformAddress();
		}
	}
	// 見つからなかった場合NULLを返す
	return NULL;
}

Vector3 ObjectManager::GetWorldPos(WorldTransform* worldTransform) {
	// 結果格納用
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform->matWorld_.m[3][0];
	worldPos.y = worldTransform->matWorld_.m[3][1];
	worldPos.z = worldTransform->matWorld_.m[3][2];

	// 結果を返す
	return worldPos;
}

void ObjectManager::SetTimeScale(int value, float timeScale) {
	// 固有速度有効
	objects_[value]->SetEnableMyTimeScale(true);
	// 速度セット
	objects_[value]->SetTimeScale(timeScale);
}

void ObjectManager::SetTimeScale(ObjectTag tag, float timeScale) {
	for (int i = 0; i < kMaxAliveObjects; i++) {
		// 引数のタグと一致するオブジェクトを検索する
		if (objects_[i]->GetIsAlive() && objects_[i]->GetTag() == tag) {
			// 固有速度有効
			objects_[i]->SetEnableMyTimeScale(true);
			// 速度セット
			objects_[i]->SetTimeScale(timeScale);
		}
	}
}

void ObjectManager::SetEnableMyTimeScale(ObjectTag tag, bool enable) {
	for (int i = 0; i < kMaxAliveObjects; i++) {
		// 引数のタグと一致するオブジェクトを検索する
		if (objects_[i]->GetIsAlive() && objects_[i]->GetTag() == tag) {
			// 固有速度有効
			objects_[i]->SetEnableMyTimeScale(enable);
		}
	}
}

void ObjectManager::CheckCollision(BaseObject* object) {
	// 生存状態が生存中のオブジェクトを探す
	for (int i = 0; i < kMaxAliveObjects; i++) {
		// 生存状態のオブジェクトを見つけた場合
		if (objects_[i]->GetIsAlive() && object != objects_[i]) {
			if (CollisonManager::IsCollison(
			        GetWorldPos(object->GetWorldTransformAddress()), object->GetObjectRadius(),
			        GetWorldPos(objects_[i]->GetWorldTransformAddress()),
			        objects_[i]->GetObjectRadius())) {
				object->OnHit(objects_[i]->GetType());
				objects_[i]->OnHit(object->GetType());
			}
		}
	}
}
