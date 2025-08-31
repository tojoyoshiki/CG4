#pragma once
#include <KamataEngine.h>

class Player {
public:
	void Initialize(KamataEngine::Model* model);
	void Update();
	void Draw(KamataEngine::Camera& camera);
	void SpriteDraw();

private:
	KamataEngine::Model* model_;
	KamataEngine::WorldTransform worldtransform;

	uint32_t HpGageRedId;
	uint32_t HpGageGreId;
	uint32_t numbers[5];
	int num;
};
