#include "TitleScene.h"
void TitleScene::Initialize() {
	// ワールド変換の初期化
	worldTransform_.Initialize();
	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("title.png");
	// スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, {320, 50});

	// 進行方向フラグの初期化
	isMovingDown_ = true;

}

void TitleScene::Update() {
	// スプライトの位置を更新
	//sprite_->SetPosition({0, 0});


	Vector2 position = sprite_->GetPosition();

	if (isMovingDown_) {
		position.y += 0.5f;
		if (position.y >= 50.0f) {
			isMovingDown_ = false; // 上方向へ切り替え
		}
	} else {
		position.y -= 0.5f;
		if (position.y <= 0.0f) {
			isMovingDown_ = true; // 下方向へ切り替え
		}
	}

	sprite_->SetPosition(position);
}

void TitleScene::Draw() {
	// スプライトの描画
	//sprite_->Draw();
}