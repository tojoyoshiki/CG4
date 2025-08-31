#include "Graph.h"

void Graph::Initialize() {
	//テクスチャの読み込み
	greenTextureHandle_ = TextureManager::Load("white1x1.png");
	redTextureHandle_ = TextureManager::Load("white1x1.png");
	// スプライトの生成
	greenSprite_ = Sprite::Create(greenTextureHandle_, {0, 0});
	redSprite_ = Sprite::Create(redTextureHandle_, {0, 0});

	greenSprite_->SetPosition({100, 100});
	redSprite_->SetPosition({100, 100});
	greenSprite_->SetSize({320, 20});
	redSprite_->SetSize({320, 20});
	greenSprite_->SetColor({0, 1, 0, 0.8f}); // 緑色
	redSprite_->SetColor({1, 0, 0, 0.8f});   // 赤色

}

void Graph::Update() { 
	Vector2 spriteSize = {greenSprite_->GetSize()}; 
	spriteSize.x -= 0.1f; // サイズを少しずつ減らす
	greenSprite_->SetSize(spriteSize); // 更新されたサイズをセット
};

void Graph::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = dxCommon->GetCommandList();

	// スプライトの描画
	Sprite::PreDraw(commandList);
	redSprite_->Draw();
	greenSprite_->Draw();
	Sprite::PostDraw();
}