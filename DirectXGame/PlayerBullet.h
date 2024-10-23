#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;


class PlayerBullet {
public:
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const Camera& camera);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};