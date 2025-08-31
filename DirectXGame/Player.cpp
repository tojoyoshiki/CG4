#include "Player.h"

#include "SpriteManager/SpriteManger.h"
#include "SpriteManager/GlobalSpriteManger.h"

using namespace KamataEngine;

void Player::Initialize(KamataEngine::Model* model) { 
	model_ = model;
	worldtransform.Initialize();

	HpGageRedId = globalSpriteManager.CreateSprite("HPGageLed.png", Vector2{0.0f, 0.0f});
	HpGageGreId = globalSpriteManager.CreateSprite("HPGageGreen.png", Vector2{0.0f, 0.0f});

	globalSpriteManager.SetSpritePosition(HpGageRedId, Vector2{0.0f, 0.0f});
	globalSpriteManager.GetSprite(HpGageRedId)->SetSize(Vector2{300.0f, 20.0f});
	globalSpriteManager.GetSprite(HpGageRedId)->SetColor(Vector4{1,1,1,0.8f});
	globalSpriteManager.SetSpritePosition(HpGageGreId, Vector2{0.0f, 0.0f});
	globalSpriteManager.GetSprite(HpGageGreId)->SetSize(Vector2{300.0f, 20.0f});
	globalSpriteManager.GetSprite(HpGageGreId)->SetColor(Vector4{1, 1, 1, 0.8f});

	int i = 0;
	for (auto& number : numbers)
	{
		number = globalSpriteManager.CreateSprite("number.png", Vector2{0.0f, 0.0f});
		numbers[i] = number;
		globalSpriteManager.GetSprite(numbers[i])->SetSize(Vector2{50.0f, 50.0f});
		i++;
	}
}

void Player::Update() {
	Vector2 GreSpriteSce = globalSpriteManager.GetSprite(HpGageGreId)->GetSize();
	GreSpriteSce.x -= 0.1f;
	globalSpriteManager.GetSprite(HpGageGreId)->SetSize(GreSpriteSce);

	num++;
	if (num > 99999) {
		num = 99999;
	}

	float startX = 100.0f;
	float spacing = 35.0f;

	// 各桁の数字を抽出
	int tempNum = num;
	for (int i = 0; i < 5; i++) {
		// 現在の桁の数字を取得 (右端から)
		int digit = tempNum % 10;

		// 次の桁の準備
		tempNum /= 10;

		// テクスチャ矩形の設定
		Vector2 uvStart = Vector2{32.0f * digit, 0.0f};
		Vector2 uvSize = Vector2{32.0f, 64.0f};
		globalSpriteManager.GetSprite(numbers[i])->SetTextureRect(uvStart, uvSize);

		// スプライトの位置設定 (右詰めで表示)
		float posX = startX + (spacing * (4 - i));
		globalSpriteManager.SetSpritePosition(numbers[i], Vector2{posX, 100.0f});
	}
    worldtransform.UpdateMatrix();
}

void Player::Draw(Camera& camera) {
	
	model_->Draw(worldtransform, camera); 

}

void Player::SpriteDraw() { 
	globalSpriteManager.DrawSprite(HpGageRedId); 
	globalSpriteManager.DrawSprite(HpGageGreId); 

	for (int i = 0; i < 5; i++) {
		// CreateSprite()の引数ではなく、numbers配列に格納されたIDを渡す
		globalSpriteManager.DrawSprite(numbers[i]);
	}
}
