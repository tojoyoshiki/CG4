#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;


class TitleScene {
public:
	
	void Initialize();
	void Update();
	void Draw();

private:
	WorldTransform worldTransform_;

	uint32_t textureHandle_ = 0;
	Sprite*sprite_;
	// 進行方向フラグの初期化
	bool isMovingDown_;
};
