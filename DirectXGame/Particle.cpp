#include "Particle.h"
using namespace KamataEngine;
using namespace MathUtility;
#include <algorithm>
#include <cassert>


Particle::Particle() {}

Particle::~Particle() {}

void Particle::Initialize(Model* model, Vector3 position, Vector3 velocity) {
	//NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	// ワールド変換の初期化
	worldTransform_.Initialize();

	//色の設定
	objectColor_.Initialize();
	color_ = {1, 1, 0, 1};

	worldTransform_.translation_ = position;

	velocity_ = velocity;

	//大きさ
	worldTransform_.scale_ = {0.2f, 0.2f, 0.2f};

}

void Particle::Update() {
	
	// 終了なら何もしない
	if (isFinished_) {
		return;
	}

	// カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;

	// 存続時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		// 終了扱いにする
		isFinished_ = true;
	}

	//色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);

	//移動
	worldTransform_.translation_ += velocity_;

	//行列の更新
	worldTransform_.UpdateMatrix();

	//フェード処理
	color_.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);

}

void Particle::Draw(Camera& camera) {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, camera, &objectColor_); 
}
