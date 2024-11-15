#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

class PlayerBullet {
public:
	void Initialize(Model* model, const Vector3& position,const Vector3&velocity);

	void Update();

	void Draw(const Camera& camera);

	// 速度
	Vector3 velocity_;

	bool IsDead() const { return isDead_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//寿命<frm>
	static const int32_t kLifeTime = 60 * 5;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;

};
