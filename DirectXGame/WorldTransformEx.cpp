#include <KamataEngine.h>
#include <math/MathUtility.h>

using namespace KamataEngine::MathUtility;

void KamataEngine::WorldTransform::UpdateMatrix() {
	// スケーリング行列の作成
	Matrix4x4 matScale = MathUtility::MakeScaleMatrix(scale_);

	// 回転行列の作成
	Matrix4x4 matRotX = MathUtility::MakeRotateXMatrix(rotation_.x);
	Matrix4x4 matRotY = MathUtility::MakeRotateYMatrix(rotation_.y);
	Matrix4x4 matRotZ = MathUtility::MakeRotateZMatrix(rotation_.z);
	Matrix4x4 matRot = matRotZ * matRotX * matRotY;

	// 平行移動行列の作成
	Matrix4x4 matTrans = MathUtility::MakeTranslateMatrix(translation_);

	//スケーリング、回転、平行移動の合成
	matWorld_ = matScale * matRot * matTrans;

	//定数バッファに転送する
	TransferMatrix();
}