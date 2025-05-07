#pragma once
#include <KamataEngine.h>

class Particle {
public:
	Particle();
	~Particle();

	void Initialize(KamataEngine::Model* model, 
		KamataEngine::Vector3 position, KamataEngine::Vector3 velocity);
	void Update();
	void Draw(KamataEngine::Camera& camera);
	
	//getter
	bool IsFinished() { return isFinished_;	}

	// color ゲッター／セッター
	KamataEngine::Vector4 GetColor() const { return color_; }
	void SetColor(const KamataEngine::Vector4& color) { color_ = color; }

	// 経過時間と寿命
	float GetCounter() const { return counter_; }
	float GetDuration() const { return kDuration; }

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;

    //移動量
	KamataEngine::Vector3 velocity_;
	//色変更オブジェクト
	KamataEngine::ObjectColor objectColor_;
	//色の数値
	KamataEngine::Vector4 color_;
	//終了フラグ
	bool isFinished_ = false;
	//経過時間カウント
	float counter_ = 0.0f;
	//パーティクルが消えるまでの時間(秒)
	const float kDuration = 1.0f;

};