#include "GameScene.h"
using namespace KamataEngine;
#include <random>
std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);
using namespace MathUtility;


GameScene::GameScene() {}

GameScene::~GameScene() {

	delete titleScene_;
	delete stage_;
	Model2::StaticFinalize();
	
}

void GameScene::Initialize() {
	// 3Dモデルデータの生成
	modelEffect_ = Model::CreateSphere(2, 2);

	//カメラの初期化
	camera_. Initialize();
	
	Normalize(velocity);
	velocity *= distribution(randomEngine);
	velocity *= 0.1f;

	//乱数の初期化
	srand((unsigned)time(NULL));
	
	Model2::StaticInitialize();
	model2_ = Model2::CreateSphere(2, 2);
	model2_ = Model2::CreateSquare();
	camera_.Initialize();
	worldTransform_.Initialize();

	titleScene_ = new TitleScene();
	titleScene_->Initialize();

	stage_ = new Stage();
	stage_->Initialize();

}

void GameScene::Update() {

	// 確率で発生
	if (rand() % 20 == 0) {
		// 発生位置は乱数
		Vector3 position = {distribution(randomEngine) * 30.0f, distribution(randomEngine) * 20.0f, 0};

		//パーティクル発生
		EffectBorn(position);
	
	}

	// 終了フラグの立ったパーティクルを削除
	effects_.remove_if([](Effect* effect) {
		if (effect->IsFinished()) {
			delete effect; // メモリ解放
			return true;     // 削除する
		}
		return false; // 削除しない
	});
	
	// パーティクルの更新
	for (Effect* effect : effects_) {
		effect->Update();
	}

	titleScene_->Update();
	stage_->Update();
}

void GameScene::Draw() {
	//DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//3Dモデル描画前処理
	Model2::PreDraw(dxCommon->GetCommandList());

	//model2_->Draw(worldTransform_, camera_);

	// 3Dモデル描画後処理
	Model2::PostDraw();

	Sprite::PreDraw(dxCommon->GetCommandList());
	titleScene_->Draw();
	stage_->Draw();
	Sprite::PostDraw();

}

void GameScene::EffectBorn(KamataEngine::Vector3 position) {
	for (int i = 0; i < 10; i++) {
		// パーティクルの生成
		Effect* effect = new Effect();
		// 位置
		Vector3 position_ = position;

		float size = abs(distribution(randomEngine) * 5.0f);
		float rotation = (distribution(randomEngine) * 3.0f);


		// 移動量
		velocity = {distribution(randomEngine), distribution(randomEngine), 0};
		// パーティクルの初期化
		effect->Initialize(modelEffect_, position_, velocity,size,rotation);
		// リストに追加
		effects_.push_back(effect);

		// ランダムな色を生成（0.0～1.0の範囲）
		float r = static_cast<float>(rand()) / RAND_MAX;
		float g = static_cast<float>(rand()) / RAND_MAX;
		float b = static_cast<float>(rand()) / RAND_MAX;

		// 色をランダムに設定
		effect->color_ = {r, g, b};

	}
}
