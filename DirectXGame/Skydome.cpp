#include "Skydome.h"
#include "MathUtilityForText.h"
#include <cassert>
#include "Affine.h"

void Skydome::Initialize(Model* model, Camera* camera) {
	assert(model);
	model_ = model;
	camera_ = camera;
	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Skydome::Update() {

	worldTransform_.rotation_.y -= 0.0001f;
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Skydome::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }
