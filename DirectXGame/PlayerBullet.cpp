#include "PlayerBullet.h"
#include<cassert>
using namespace MathUtility;
void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	//NULLポインタチェック
	assert(model);
	model_ = model;

	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("black1x1.png");

	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;

}

void PlayerBullet::Update() {
	worldTransform_.UpdateMatrix();
	//座標を移動させる（1フレーム分の移動量を足しこむ）
	worldTransform_.translation_ += velocity_;

	//時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	

}

void PlayerBullet::Draw(const Camera& camera) {
	//モデルの描画
	model_->Draw(worldTransform_, camera, textureHandle_);
}
