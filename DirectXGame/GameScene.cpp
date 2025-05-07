#include "GameScene.h"
#include <random>
#include <algorithm>

using namespace KamataEngine;
using namespace MathUtility;

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete modelParticle_;
	for (Particle* particle : particles_) {
	delete particle;
	}
	particles_.clear();
}

void GameScene::Initialize() {
	// 3dモデルデータの生成
	modelParticle_ = Model::CreateSphere(4, 4);
	// cameraの初期化
	camera_.Initialize();
	// particleの生成
	for (int i = 0; i < 150; i++) {
     	//生成
		Particle* particle = new Particle();
		//位置
		KamataEngine::Vector3 position = {0.0, 0.0f, 0.0f};
	    //移動量
		KamataEngine::Vector3 velocity = 
		{distribution(randomEngine), 
			distribution(randomEngine), 0};
		//初期化
		particle->Initialize(modelParticle_, position, velocity);
		//リストに追加
		particles_.push_back(particle);
		Normalize(velocity);
		velocity *= distribution(randomEngine);
		velocity *= 0.1f;
	}
}

void GameScene::Update() {
	for (Particle* particle : particles_) {
		particle->Update();

		// フェード処理
		KamataEngine::Vector4 color = particle->GetColor();
		float alpha = std::clamp(1.0f - particle->GetCounter() / particle->GetDuration(), 0.0f, 1.0f);
		color.w = alpha;
		particle->SetColor(color);
	}

	// 終了フラグが立ったパーティクルを削除
	particles_.remove_if([](Particle* particle) {
		if (particle->IsFinished()) {
			delete particle;
			return true;
		}
		return false;
	});
}

void GameScene::Draw() {

	// DXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());
	// ぱーてぃくるびょうが　
	for (Particle* particle : particles_) {
	particle->Draw(camera_);
	}
	// 3dモデル描画後処理
	Model::PostDraw();
}