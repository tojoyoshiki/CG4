#include "Particle.h"

Particle::Particle() {}

Particle::~Particle() {}

void Particle::Initialize(KamataEngine::Model* model) {
	assert(model);

	model = model_; // 引数から受け取ったデータをメンバ変数に記録する
	worldTransform_.translation_.z = 0.0f;
	worldTransform_.Initialize(); // ワールド変換の初期化
}

void Particle::Update() { worldTransform_.TransferMatrix(); }

void Particle::Draw(KamataEngine::Camera& camera) { model_->Draw(worldTransform_, camera); }
