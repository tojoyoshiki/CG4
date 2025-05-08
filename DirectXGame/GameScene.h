#pragma once
#include "Particle.h"
#include <KamataEngine.h>

class GameScene {
public:
	GameScene();
	~GameScene();
	void Initialize();
	void Update();
	void Draw();

	// パーティクル発生
	void ParticleBorn(KamataEngine::Vector3 position);

private:
	KamataEngine::Model* modelParticle_ = nullptr;
	KamataEngine::Camera camera_;
	std::list<Particle*> particles_;
};
