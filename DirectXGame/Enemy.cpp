#include "Enemy.h"
#include "MathUtilityForText.h"
#include "Player.h"
#include <cassert>
#include "Affine.h"
using namespace MathUtility;

void Enemy::Initialize(Model* model, uint32_t textureHandle) {

	// NULLポインタチェック
	assert(model);
	// シングルインスタンスを取得する
	input_ = Input::GetInstance();
	// メンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;
	// ワールド変換の初期化
	worldTransform_.Initialize();
	flag = 0;
	timer = 0.0f;
}

void Enemy::Approach() {

	// 座標移動（ベクトルの加算）
	worldTransform_.translation_.z -= 0.1f;

	// worldTransform_.translation_.x = 1.0f;

	// キャラクターの移動速さ
	const Vector3 kCharacterSpeed = {0.05f, 0.05f, 0.05f};


	// 移動（ベクトルを加算）
	worldTransform_.translation_ += kCharacterSpeed;
	// 規定の位置に到達したら離脱
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave() {

	// 座標移動（ベクトルの加算）
	worldTransform_.translation_.z -= 0.1f;

	// worldTransform_.translation_.x = 1.0f;

	// キャラクターの移動速さ
	const Vector3 kCharacterSpeed = {0.05f, 0.05f, 0.05f};
	// 移動（ベクトルを加算）
	worldTransform_.translation_ += kCharacterSpeed;
}

void Enemy::Fire() {

	timer++;
	if (timer >= 20.0f) {
		flag = 1;
	} else {
		flag = 0;
	}

	if (flag == 1) {

		const float kEnemyBulletSpeed = 0.5f;

		// 座標の取得
		Vector3 targetPos = player_->GetWorldPosition();
		Vector3 basePos = this->GetWorldPosition();
		Vector3 velocity = targetPos - basePos;

		velocity = Normalize(velocity);

		velocity *= kEnemyBulletSpeed;
		// velocity = TransformNormal(velocity, worldTransform_.matWorld_);

		if (enemyBullet_) {
			delete enemyBullet_;
			enemyBullet_ = nullptr;
		}
		EnemyBullet* newEnemyBullet = new EnemyBullet();
		newEnemyBullet->Initialize(model_, worldTransform_.translation_, velocity);
		// enemyBullet_ = newEnemyBullet;
		enemyBullets_.push_back(newEnemyBullet);
		timer = 0.0f;
	}
}

void Enemy::OnCollision() {}

void Enemy::Update() {

	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// 敵のフェーズ
	switch (phase_) {
	case Enemy::Phase::Approach:
	default:

		Approach();

		break;
	case Enemy::Phase::Leave:

		Leave();

		break;
	}

	Fire();

	/*if (enemyBullet_) {
	    enemyBullet_->Update();
	}*/

	for (EnemyBullet* enemyBullet : enemyBullets_) {

		enemyBullet->Update();
	}

	

	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Enemy::Draw(Camera& camera) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, camera, textureHandle_);

	/*if (enemyBullet_) {
	    enemyBullet_->Draw(camera);
	}*/

	for (EnemyBullet* enemyBullet : enemyBullets_) {

		enemyBullet->Draw(camera);
	}
}

Enemy::~Enemy() { delete enemyBullet_; }

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}
