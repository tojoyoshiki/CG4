#pragma once
#include "Particle.h"
#include "Effect.h"
#include "KamataEngine.h"
#include "Model2.h"
#include "TitleScene.h"
#include "Stage.h"

using namespace KamataEngine;

class GameScene {
public:
	GameScene();
	~GameScene();
	void Initialize();
	void Update();
	void Draw();

	/// <summary>
	/// パーティクル発生
	/// </summary>
	/// <>param name="position">位置</param>
	void EffectBorn(Vector3 position);

private:
	//パーティクル3D
	Model* modelEffect_ = nullptr;
	//カメラ
	Camera camera_;
	//パーティクル
	Effect* effect_ = nullptr;

	std::list<Effect*> effects_;

	Vector3 velocity;

	Model2* model2_ = nullptr;

	WorldTransform worldTransform_;

	TitleScene* titleScene_ = nullptr;
	Stage* stage_ = nullptr;

};
