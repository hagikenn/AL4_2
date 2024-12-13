#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include "EnemyBullet.h"

// 自機クラスの前方宣言
class Player;

class Enemy {

public:
	// 行動フェーズ
	enum class Phase {
		Approach,
		Leave,
	};

	Phase phase_ = Phase::Approach;

	// キーボード入力
	Input* input_ = nullptr;

	void Initialize(Model* model, uint32_t textureHandle);

	void Approach();

	void Leave();

	void Fire();

	// 衝突を検出したらコールバック
	void OnCollision();

	// 弾リストを取得
	const std::list<EnemyBullet*>& GetBullets() const { return enemyBullets_; }

	void Update();

	void Draw(Camera& camera);

	~Enemy();

	// 弾
	EnemyBullet* enemyBullet_ = nullptr;

	std::list<EnemyBullet*> enemyBullets_;

	int flag;
	float timer;

	// 自キャラ
	Player* player_ = nullptr;

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};
