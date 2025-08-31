#include "Number.h"

//void Number::Initialize() {
//	textureHandle = TextureManager::Load("number.png");
//	for (int i = 0; i < 5; ++i) {
//		sprite[i] = Sprite::Create(textureHandle, {100.0f+size.x*i,5});
//		sprite[i]->SetSize(size);
//	}
//}
//
//void Number::Update() {
//	for (int i = 0; i < 5; ++i) {
//		sprite[i]->SetTextureRect({0,0},size);
//	}
//	hp -= 1;
//	if (hp < 0) {
//		hp = 0;
//	}
//}
//
//void Number::Draw() {
//	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();
//	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
//
//	Sprite::PreDraw(commandList);
//	digit = 10000;
//	number = hp;
//
//	for (int i = 0; i < 5; ++i) {
//		int nowNumber = number / digit; 
//		sprite[i]->SetTextureRect(uvStart, size); // UV座標を設定
//		sprite[i]->Draw(); // スプライトを描画
//		digit /= 10; // 次の桁へ
//	}
//
//}
