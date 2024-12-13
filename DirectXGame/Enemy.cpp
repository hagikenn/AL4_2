#include "Enemy.h"

Enemy::~Enemy() {
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;

	// ワールド座標の初期化
	worldTransform_.Initialize();

	flag = 0;
	timer = 0.0f;

}

void Enemy::Update() {

	// 座標移動（ベクトルの加算）
	worldTransform_.translation_.z -= 0.1f;

		//worldTransform_.translation_.x = 1.0f;


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

	// 敵攻撃処理
	Fire();
	// 弾更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

	// デスフラグの立った弾を削除
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

}

void Enemy::Draw(Camera& camera) {
	model_->Draw(worldTransform_,camera,textureHandle_); 

	// 弾の描画
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(camera);
	}
}

void Enemy::Fire() {
	timer++;

	if (timer >= 50.0f) {
		flag = 1;
	} else {
		flag = 0;
	}

	if (flag == 1) {
		if (bullet_) {
			delete bullet_;
			bullet_ = nullptr;
		}
		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		// 速度ベクトルを自機の向きに合わせて回転させる
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);

		// 弾を生成し、初期化
		EnemyBullet* newBullet = new EnemyBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);
		timer = 0.0f;
	}


	
}
