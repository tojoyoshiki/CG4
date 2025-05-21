#include "GameScene.h"
#include <algorithm>
#include <random>

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

	srand((unsigned)time(NULL));
}

void GameScene::Update() {

	// 終了フラグが立ったパーティクルを削除
	particles_.remove_if([](Particle* particle) {
		if (particle->IsFinished()) {
			delete particle;
			return true;
		}
		return false;
	});

	// 確率で新しいパーティクルを生成
	if (rand() % 20 == 0) {
		KamataEngine::Vector3 position = {distribution(randomEngine) * 30.0f, distribution(randomEngine) * 20.0f, 0};
		ParticleBorn(position);
	}

		// パーティクル更新
	for (Particle* particle : particles_) {
		particle->Update();

		// フェード処理
		KamataEngine::Vector4 color = particle->GetColor();
		float alpha = std::clamp(1.0f - particle->GetCounter() / particle->GetDuration(), 0.0f, 1.0f);
		color.w = alpha;
		particle->SetColor(color);
	}
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

void GameScene::ParticleBorn(KamataEngine::Vector3 position) {
	for (int i = 0; i < 150; i++) {
		Particle* particle = new Particle();
		KamataEngine::Vector3 velocity = {distribution(randomEngine), distribution(randomEngine), 0};
		Normalize(velocity);
		velocity *= distribution(randomEngine);
		velocity *= 0.1f;

		// ランダムな色
		KamataEngine::Vector4 color = {
		    distribution(randomEngine) * 0.8f + 0.2f, // R
		    distribution(randomEngine) * 0.8f + 0.2f, // G
		    distribution(randomEngine) * 0.8f + 0.2f, // B
		    1.0f};

		// 初期化
		particle->Initialize(modelParticle_, position, velocity);
		particle->SetColor(color);

		// リストに追加
		particles_.push_back(particle);
	}
}
