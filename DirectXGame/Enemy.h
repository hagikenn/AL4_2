#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include"MathUtilityForText.h"


class Enemy {
public:
	enum class Phase {
		Approach,//接近する
		Leave,//離脱する
	};

	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(Camera& camera);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//フェーズ
	Phase phase_ = Phase::Approach;

};
