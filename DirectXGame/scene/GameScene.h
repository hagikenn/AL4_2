#pragma once

#include <KamataEngine.h>
using namespace KamataEngine;

#include"../Player.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Player* player_ = nullptr;
	Model* model_ = nullptr;
	DebugCamera* debugCamera_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	WorldTransform worldTransform_;
	
	//カメラ
	Camera camera_;

	float inputFloat3[3] = {0, 0, 0};

	//デバックカメラ有効
	bool isDebugCameraActive_ = false;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
