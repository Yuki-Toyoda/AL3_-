#include "ParticleManager.h"
#include "BaseManager.h"
#include "ObjectManager.h"

#pragma region private
ParticleManager::ParticleManager() {}

ParticleManager::~ParticleManager() {
	// オブジェクトをリリース
	for (int i = 0; i < kMaxAliveParticle; i++) {
		delete particles_[i];
	}
}
#pragma endregion

#pragma region public

ParticleManager* ParticleManager::GetInstance() {
	// 関数内Static変数として宣言
	static ParticleManager instance;
	return &instance;
}

void ParticleManager::Initialize() { 

	// パーティクルのインスタンスを生成
	for (int i = 0; i < kMaxAliveParticle; i++) {
		particles_[i] = new BaseParticle();
		particles_[i]->Initialize();

		// Imguiでの生成を行うための変数の初期化
		enableMyTimeScale_[i] = false;
		isEnd_[i] = false;
		stilContinuation_[i] = true;

	}

	// Imguiでの生成を行うための変数の初期化
	spawnTranslate_ = {0.0f, 5.0f, 0.0f};
	setTranslate_ = {0.0f, 5.0f, 0.0f};
	setTimeScale_ = 1.0f;
	select_ = TagNone;
	tag_ = TagNone;

}

void ParticleManager::Update() {

	// オブジェクトのデバック表示
	ImGui::Begin("Particles");

	// セットする際の値を設定
	ImGui::DragFloat3("setTranslate", &setTranslate_.x, 0.05f);
	ImGui::DragFloat("setTImeScale", &setTimeScale_, 0.01f, kMinTimeScale, kMaxTimeScale);
	// 有効タグを調べる
	ImGui::RadioButton("TagNone", &select_, TagNone);
	ImGui::SameLine();
	ImGui::RadioButton("TagPlayer", &select_, TagPlayer);
	ImGui::SameLine();
	ImGui::RadioButton("TagEnemy", &select_, TagEnemy);

	// 生成されているパーティクルを更新する
	for (int i = 0; i < kMaxAliveParticle; i++) {
		if (particles_[i]->GetType() != ParticleDefault) {
			particles_[i]->Update();
		}

		// Imguiで敵の座標などを表示、設定する
		if (!particles_[i]->GetIsEnd() && particles_[i]->GetType() != ParticleDefault) {

			char tree[16] = "";
			sprintf_s(tree, "Particle%d", i);

			if (ImGui::TreeNode(tree)) {

				// オブジェクトの現在座標を取得
				Vector3 translate = particles_[i]->GetWorldTransform().translation_;
				// Imguiで表示
				ImGui::DragFloat3("translate", &translate.x, 0.05f);
				// 改行しない
				ImGui::SameLine();
				// セットボタンを押すと座標をセットする
				if (ImGui::Button("SetTranslate")) {
					particles_[i]->SetTranslation(setTranslate_);
				}

				// チェックボックスによってパーティクルの再生、一時停止を行う
				if (ImGui::Checkbox("continuation", &stilContinuation_[i])) {
					particles_[i]->SetIsAlive(stilContinuation_[i]);
				}

				// チェックボックスによってパーティクルの再生、一時停止を行う
				if (ImGui::Checkbox("End", &isEnd_[i])) {
					particles_[i]->SetIsEnd(isEnd_[i]);
				}

				// オブジェクトのタイムスケールを取得
				float timeScale = particles_[i]->GetTimeScale();
				// Imguiで表示
				ImGui::DragFloat("timeScale", &timeScale, 0.05f);
				// 改行しない
				ImGui::SameLine();
				// セットボタンを押すと座標をセットする
				if (ImGui::Button("SetTimeScale")) {
					particles_[i]->SetTimeScale(setTimeScale_);
				}

				// チェックボックスによって固有の速度を有効にするか決める
				if (ImGui::Checkbox("EnableMyTimeScale", &enableMyTimeScale_[i])) {
					particles_[i]->SetEnableMyTimeScale(enableMyTimeScale_[i]);
				}

				// 現在のタグを取得
				ObjectTag selectTag = particles_[i]->GetTag();
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
					particles_[i]->SetTag((ObjectTag)select_);
				}

				ImGui::TreePop();
			}
		}

	}

	ImGui::End();

}

void ParticleManager::Draw() {
	// 生成されているパーティクルを描画する
	for (int i = 0; i < kMaxAliveParticle; i++) {
		if (particles_[i]->GetType() != ParticleDefault) {
			particles_[i]->Draw(BaseManager::GetInstance()->GetViewProjection());
		}
	}
}

void ParticleManager::SetTimeScale(int value, float timeScale) {
	// 固有速度有効
	particles_[value]->SetEnableMyTimeScale(true);
	// 速度セット
	particles_[value]->SetTimeScale(timeScale);
}

void ParticleManager::SetTimeScale(ObjectTag tag, float timeScale) {
	for (int i = 0; i < kMaxAliveParticle; i++) {
		// 引数のタグと一致するオブジェクトを検索する
		if (!particles_[i]->GetIsEnd() && particles_[i]->GetTag() == tag) {
			// 固有速度有効
			particles_[i]->SetEnableMyTimeScale(true);
			// 速度セット
			particles_[i]->SetTimeScale(timeScale);
		}
	}
}

void ParticleManager::SetEnableMyTimeScale(ObjectTag tag, bool enable) {
	for (int i = 0; i < kMaxAliveParticle; i++) {
		// 引数のタグと一致するオブジェクトを検索する
		if (!particles_[i]->GetIsEnd() && particles_[i]->GetTag() == tag) {
			// 固有速度有効
			particles_[i]->SetEnableMyTimeScale(enable);
		}
	}
}

#pragma endregion
