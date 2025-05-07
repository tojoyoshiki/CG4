#pragma once
#include <KamataEngine.h>
#include "Particle.h"

class GameScene {
public:
	GameScene();
	~GameScene();
	void Initialize();
	void Update();
	void Draw();

	private:
	KamataEngine::Model* modelParticle_ = nullptr;
	KamataEngine::Camera camera_;
	std::list<Particle*> particles_;
};
