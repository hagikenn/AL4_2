#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;

	// ワールド座標の初期化
	worldTransform_.Initialize();
}

void Enemy::Update() {
	// 座標移動（ベクトルの加算）
	worldTransform_.translation_.z -= 0.1f;

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(Camera& camera) {
	model_->Draw(worldTransform_,camera,textureHandle_);
}
