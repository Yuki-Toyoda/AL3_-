#include "SpriteManager.h"
#include "BaseManager.h"

SpriteManager::SpriteManager() {}

SpriteManager::~SpriteManager() {
	// スプライトをリリース
	for (int i = 0; i < kMaxSpriteCount; i++) {
		delete sprites_[i];
	}
}

SpriteManager* SpriteManager::GetInstance() {
	// 関数内Static変数として宣言
	static SpriteManager instance;
	return &instance;
}

void SpriteManager::Initialize() {

	// 全てのスプライトを初期化する
	for (int i = 0; i < kMaxSpriteCount; i++) {
		sprites_[i] = new BaseSprite();
		sprites_[i]->Initialize();

		// Imguiでの生成を行うための変数の初期化
		enableMyTimeScale_[i] = false;

	}

	// Imguiでの生成を行うための変数の初期化
	setTranslate_ = {0.0f, 0.0f};
	setTimeScale_ = 1.0f;
	select_ = TagNone;
	tag_ = TagNone;

}

void SpriteManager::Update() {

	// スプライトのデバック表示
	ImGui::Begin("Sprite");

	// セットする際の値を設定
	ImGui::DragFloat2("setTranslate", &setTranslate_.x, 0.05f);
	ImGui::DragFloat("setTImeScale", &setTimeScale_, 0.01f, kMinTimeScale, kMaxTimeScale);
	// 有効タグを調べる
	ImGui::RadioButton("TagNone", &select_, TagNone);
	ImGui::SameLine();
	ImGui::RadioButton("TagPlayer", &select_, TagPlayer);
	ImGui::SameLine();
	ImGui::RadioButton("TagEnemy", &select_, TagEnemy);

	for (int i = 0; i < kMaxSpriteCount; i++) {
		if (sprites_[i]->GetType() != SpriteNone) {
			sprites_[i]->Update();
		}

		// Imguiで敵の座標などを表示、設定する
		if (sprites_[i]->GetIsAlive() && sprites_[i]->GetType() != SpriteNone) {

			char tree[16] = "";
			sprintf_s(tree, "Sprite%d", i);

			if (ImGui::TreeNode(tree)) {

				// オブジェクトの現在座標を取得
				Vector2 translate = sprites_[i]->GetSpriteTranslate();
				// Imguiで表示
				ImGui::DragFloat2("translate", &translate.x, 0.05f);
				// 改行しない
				ImGui::SameLine();
				// セットボタンを押すと座標をセットする
				if (ImGui::Button("SetTranslate")) {
					sprites_[i]->SetSpriteTranslate(setTranslate_);
				}

				// オブジェクトのタイムスケールを取得
				float timeScale = sprites_[i]->GetTimeScale();
				// Imguiで表示
				ImGui::DragFloat("timeScale", &timeScale, 0.05f);
				// 改行しない
				ImGui::SameLine();
				// セットボタンを押すと座標をセットする
				if (ImGui::Button("SetTimeScale")) {
					sprites_[i]->SetTimeScale(setTimeScale_);
				}

				// チェックボックスによって固有の速度を有効にするか決める
				if (ImGui::Checkbox("EnableMyTimeScale", &enableMyTimeScale_[i])) {
					sprites_[i]->SetEnableMyTimeScale(enableMyTimeScale_[i]);
				}

				// 現在のタグを取得
				ObjectTag selectTag = sprites_[i]->GetTag();
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
					sprites_[i]->SetTag((ObjectTag)select_);
				}

				ImGui::TreePop();
			}
		}
	}

	ImGui::End();
}

void SpriteManager::Draw() {
	for (int i = 0; i < kMaxSpriteCount; i++) {
		if (sprites_[i]->GetType() != SpriteNone) {
			sprites_[i]->Draw(BaseManager::GetInstance()->GetViewProjection());
		}
	}
}

void SpriteManager::SetTimeScale(int value, float timeScale) {
	// 固有速度有効
	sprites_[value]->SetEnableMyTimeScale(true);
	// 速度セット
	sprites_[value]->SetTimeScale(timeScale);
}

void SpriteManager::SetTimeScale(ObjectTag tag, float timeScale) {
	for (int i = 0; i < kMaxAliveParticle; i++) {
		// 引数のタグと一致するオブジェクトを検索する
		if (sprites_[i]->GetIsAlive() && sprites_[i]->GetTag() == tag) {
			// 固有速度有効
			sprites_[i]->SetEnableMyTimeScale(true);
			// 速度セット
			sprites_[i]->SetTimeScale(timeScale);
		}
	}
}

void SpriteManager::SetEnableMyTimeScale(ObjectTag tag, bool enable) {
	for (int i = 0; i < kMaxAliveParticle; i++) {
		// 引数のタグと一致するオブジェクトを検索する
		if (sprites_[i]->GetIsAlive() && sprites_[i]->GetTag() == tag) {
			// 固有速度有効
			sprites_[i]->SetEnableMyTimeScale(enable);
		}
	}
}

int SpriteManager::SetSpriteAnimationImage(
    float& t, int start, int end, bool isLoop) {

	// 結果格納用
	int result;

	// ループするのか
	if (isLoop) {
		if (t >= 1.0f) {
			t = 0.0f;
		}

	} else {
		if (t > 1.0f) {
			// もし引数で受け取ったtが1以上ならtを0にする
			t = 1.0f;
		} 
	}

	// イージングで表示する画像のインデックスを求める
	result = MyMath::Linear(t, start, end);

	if (result == end) {
		result -= 1;
	}

	// インデックスを返す
	return result;

}


