#include "Enemy.h"
#include "Player.h"
#include <cassert>
#include"MathUtilityForText.h"


Enemy::~Enemy() { delete bullet_; }

void Enemy::Initialize(Model* model) {
	// ワールド変換の初期化
	worldTransform_.Initialize();
	// NULLポインタをチェックする
	assert(model);
	// シングルインスタンスを取得する
	// input_ = Input::GetInstance();
	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	// textureHandle_ = textureHandle;

	worldTransform_.translation_ = {-20, 2, 20};

	// ワールド変換の初期化
	worldTransform_.Initialize();

	flag = 0;
	timer_ = 0.0f;
	// 接近フェーズ初期化
	Approach();
}

void Enemy::Update() {
	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
	if (worldTransform_.translation_.z)
		// worldTransform_.translation_.z -= 0.1f;
		// worldTransform_.rotation_.x -= 0.1f;
		model_ = Model::CreateFromOBJ("enemy");

	// デスフラグのたった弾を削除
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	worldTransform_.translation_.x += LeftRightSpeed;
	worldTransform_.translation_.y += UpDownSpeed;
	if (worldTransform_.translation_.x > 10) {
		LeftRightSpeed = -0.3f;
	}
	if (worldTransform_.translation_.y > 10) {
		UpDownSpeed = -0.3f;
	}
	if (worldTransform_.translation_.x < -10) {
		LeftRightSpeed = 0.3f;
	}
	if (worldTransform_.translation_.y < -10) {
		UpDownSpeed = 0.3f;
	}
	if (rand() % 100 == 0) {
		LeftRightSpeed *= -1;
	}
	if (rand() % 90 == 0) {
		UpDownSpeed *= -1;
	}

	// 移動
	switch (phase_) {
	case Phase::Approach:
	default:
		// 接近フェーズの更新関数
		// 移動（ベクトルを加算）
		// worldTransform_.translation_.z -= 0.1f;
		// 既定の位置に到達したら離脱
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		// 離脱フェーズの更新関数
		// 移動
		worldTransform_.translation_.x += 0.1f;
		worldTransform_.translation_.y += 0.1f;

		break;
	}

	// キャラクター攻撃処理
	Attack();

	// 弾更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Enemy::Draw(Camera& camera) {
	// modelの描画
	if (Life == true) {
		model_->Draw(worldTransform_, camera /*, textureHandle_*/);
	}

	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(camera);
	}
}

void Enemy::Approach() {
	// 発射タイマーを初期化
	firingTimer_ = kFireInterval;
}

void Enemy::Fire() {
	assert(player_);
	// 弾の速さ（調整項目）
	const float kBulletSpeed = 1.0f;
	// 自キャラのワールド座標を取得する
	Vector3 targetPos = player_->GetWorldPosition();
	// 敵キャラのワールド座標を取得する
	Vector3 basePos = this->GetWorldPosition();
	// 敵キャラ→自キャラの差分ベクトル
	Vector3 velocity = targetPos - basePos;
	// ベクトルの正規化
	velocity = Normalize(velocity);
	// ベクトルの長さを、早さに合わせる

	velocity *= kBulletSpeed;

	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	// 弾を登録する
	bullets_.push_back(newBullet);
}

void Enemy::Attack() {
	timer_++;
	if (timer_ >= 10.0f) {
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
		//	const float kBulletSpeed = 1.0f;
		//	Vector3 velocity = {0, 0, kBulletSpeed};
		// 弾を生成し、初期化
		/*EnemyBullet* newBullet = new EnemyBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);*/
		Fire();
		// 弾を登録する
		// bullets_.push_back(newBullet);
		timer_ = 0.0f;
	}
}

void Enemy::OnCollision(const Player* player) {
	(void)player;
	/*isDead_ = true;
	isFinished_ = true;
	Life = false;*/
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}
