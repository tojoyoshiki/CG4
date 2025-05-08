#include "Particle.h"
#include "math/MathUtility.h"

using namespace KamataEngine::MathUtility;

Particle::Particle() {}

Particle::~Particle() {}

void Particle::Initialize(KamataEngine::Model* model,
	KamataEngine::Vector3 position, KamataEngine::Vector3 velocity) {
	assert(model);

	model_ = model; // 引数から受け取ったデータをメンバ変数に記録する
	worldTransform_.translation_ = position;
	worldTransform_.Initialize(); // ワールド変換の初期化
	worldTransform_.scale_ = {0.2f, 0.2f, 0.2f}; // 大きさを調整

	//受け取った移動量をメンバ変数に代入する
	velocity_ = velocity;

	// 色の設定
	objectColor_.Initialize();
	color_ = {1, 1, 0, 1};
}

void Particle::Update() {
	worldTransform_.TransferMatrix();

	//色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);

	//移動
	worldTransform_.translation_ += velocity_;
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();
	//行列を更新
	worldTransform_.UpdateMatrix();

	//終了なら何もしない
	if (isFinished_) {
		return;
	}
	//カウンターを１フレーム粉の秒進める
	counter_ += 1.0f / 60.0f;
	//消えるまで進んだら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		//終了扱いにする
		isFinished_=true;
	}
}

void Particle::Draw(KamataEngine::Camera& camera) {
	model_->Draw(worldTransform_, camera, &objectColor_); 
}
