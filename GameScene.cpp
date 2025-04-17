#include "GameScene.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete modelParticle_;
	delete particle_;
}

void GameScene::Initialize() {
	// 3dモデルデータの生成
	modelParticle_ = Model::CreateSphere(4, 4);
	// cameraの初期化
	camera_.Initialize();
	// particleの生成
	particle_ = new Particle();
	// particleの初期化
	particle_->Initialize(modelParticle_);
}

void GameScene::Update() { particle_->Update(); }

void GameScene::Draw() {
	// DXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());
	// ぱーてぃくるびょうが　
	particle_->Draw(camera_);
	// 3dモデル描画後処理
	Model::PostDraw();
}