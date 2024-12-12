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

	// キャラクターの移動速さ
	const Vector3 kCharacterSpeed = {0.05f, 0.05f, 0.05f};

	worldTransform_.UpdateMatrix();

	switch (phase_) {
	case Enemy::Phase::Approach:
	default:
		//移動（ベクトルを加算）
		worldTransform_.translation_ += kCharacterSpeed;
		//規定の位置に到達したら離脱
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Enemy::Phase::Leave:
		//移動（ベクトルを加算）
		worldTransform_.translation_ += kCharacterSpeed;
		break;
	}

}

void Enemy::Draw(Camera& camera) {
	model_->Draw(worldTransform_,camera,textureHandle_);
}
