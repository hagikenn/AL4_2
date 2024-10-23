#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include"MathUtilityForText.h"
#include "PlayerBullet.h"




class Player {
public:
	void Initialize(Model*model,uint32_t textureHandle);

	void Update();

	void Draw(Camera&camera);

	void Rotate();

	void Attack();

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
	PlayerBullet* bullet_ = nullptr;

};
