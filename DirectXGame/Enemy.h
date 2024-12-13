#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include"MathUtilityForText.h"
#include"EnemyBullet.h"


class Enemy {
public:
	enum class Phase {
		Approach,//接近する
		Leave,//離脱する
	};

	// デストラクタ
	~Enemy();

	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(Camera& camera);

	/// <summary>
	/// 弾発射
	/// </summary>
	void Fire();

	// 弾
	std::list<EnemyBullet*> bullets_;

	int flag;
	float timer;

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//フェーズ
	Phase phase_ = Phase::Approach;

	//発射タイマー
	int32_t firingTimer_ = 0;

	//弾
	EnemyBullet* bullet_ = nullptr;


};
