#pragma once
#include "PlayerBullet.h"
#include <list>

#include <KamataEngine.h>
using namespace KamataEngine;

class Enemy;
class MobEnemy;

class Player {
public:
	// キーボード入力
	Input* input_ = nullptr;
	// デストラクタ
	~Player();

	void Initialize(Model* model, const Vector3& position);

	void Update();
	void Draw(Camera& viewProjection);
	void Rotate();
	void Attack();
	Vector3 GetPosition() { return worldTransform_.translation_; }

	std::list<PlayerBullet*> bullets_;
	std::list<PlayerBullet*> GetBullet() { return bullets_; }

	Vector3 GetWorldPosition();
	void OnCollision(const Enemy* enemy);
	void OnCollision(const MobEnemy* mobEnemy);

	bool IsFinished() { return finished_; }

	// デスフラグ
	bool isDead_ = false;
	// デスフラグのgetter
	bool IsDead() const { return isDead_; }

private:
	// 終了フラグ
	bool finished_ = false;
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Vector3* position_ = nullptr;
	// ImGuiで値を入力する変数
	float inputFloat3[3] = {0, 0, 0};
	// 弾
	PlayerBullet* bullet_ = nullptr;
	// 命
	bool Life = true;

	uint32_t soundDataHandle_ = 0;
	Audio* audio_ = nullptr;
};
