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

	// 確率で発生
	if (rand() % 20 == 0) {
		// 発生位置は乱数
		KamataEngine::Vector3 position = {distribution(randomEngine) * 30.0f, distribution(randomEngine) * 20.0f, 0};
		// パーティクルの生成
		ParticleBorn(position);
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
	// particleの生成
	for (int i = 0; i < 150; i++) {
		// 生成
		Particle* particle = new Particle();

		// 移動量
		KamataEngine::Vector3 velocity = {distribution(randomEngine), distribution(randomEngine), 0};

		// 移動量の正規化と調整
		Normalize(velocity);
		velocity *= distribution(randomEngine);
		velocity *= 0.1f;

		// 初期化（引数のpositionを使う）
		particle->Initialize(modelParticle_, position, velocity);

		// リストに追加
		particles_.push_back(particle);
	}
}
