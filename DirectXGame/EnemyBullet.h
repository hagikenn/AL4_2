#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

class EnemyBullet {

public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void OnCollision();

	Vector3 GetWorldPosition();

	void Update();

	void Draw(const Camera& camera);

	Vector3 velocity_;

	static const int32_t kLifeTime = 60 * 5;

	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;

	bool IsDead() const { return isDead_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};