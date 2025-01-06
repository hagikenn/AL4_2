#pragma once
#include "EnemyBullet.h"
#include <KamataEngine.h>
using namespace KamataEngine;

class Player; // 自機クラスの前方宣言

// 行動フェーズ
enum class Phase {
	Approach, // 接近する
	Leave,    // 離脱する
};

class Enemy {
public:
	~Enemy();
	void Initialize(Model* model);
	void Update();
	void Draw(Camera& viewProjection);
	void Approach();

	// 弾の発射に使う
	void Fire();
	void Attack();

	Vector3 GetPosition() { return worldTransform_.translation_; }
	std::list<EnemyBullet*> bullets_;
	std::list<EnemyBullet*> GetBullet() { return bullets_; }
	// 発射間隔	// 衝突応答
	static const int kFireInterval = 60;

	int flag;
	float timer_;
	// 衝突応答
	void OnCollision(const Player* player);

	bool IsFinished() { return isFinished_; }

	// デスフラグ
	bool isDead_ = false;
	// デスフラグのgetter
	bool IsDead() const { return isDead_; }

	// 自キャラ
	Player* player_ = nullptr;
	void SetPlayer(Player* player) { player_ = player; }
	Vector3 GetWorldPosition();

	// キーボード入力	public:
	Input* input_ = nullptr;

private:
	// 終了フラグ
	bool isFinished_ = false;
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	// uint32_t textureHandle_ = 0u;
	// Model* enemyText_ = nullptr;
	Vector3 velocityLeave_ = {-0.3f, 0.3f, -0.1f};
	float LeftRightSpeed = 0.3f;
	float UpDownSpeed = 0.3f;

	// 弾
	EnemyBullet* bullet_ = nullptr;
	// 命
	bool Life = true;
	// フェーズ
	Phase phase_ = Phase::Approach;
	// 発射タイマー
	int32_t firingTimer_ = 0;
};
