#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;


class Graph {
public:
	void Initialize();
	void Update();
	void Draw();

private:
	Sprite* greenSprite_ = nullptr;
	uint32_t greenTextureHandle_ = 0u;
	Sprite* redSprite_ = nullptr;
	uint32_t redTextureHandle_ = 0u;
};
