#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include"MathUtilityForText.h"
#include "PlayerBullet.h"
#include"Enemy.h"
#include<list>



class Player {
public:
	//デストラクタ
	~Player();

	void Initialize(Model*model,uint32_t textureHandle);

	void Update();

	void Draw(Camera&camera);

	void Rotate();

	void Attack();

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	Vector3 GetPosition() { return worldTransform_.translation_; }


	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision(const Enemy* enemy);

	std::list<PlayerBullet*> GetBullet() { return bullets_; }


	//弾リストを取得
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//キーボード入力
	Input* input_ = nullptr;

	//弾
	/*PlayerBullet* bullet_ = nullptr;*/
	std::list<PlayerBullet*> bullets_;

};
