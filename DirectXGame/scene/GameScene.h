#pragma once

#include <KamataEngine.h>
using namespace KamataEngine;
#include "../Enemy.h"
#include "../EnemyBullet.h"
#include "../Player.h"

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

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// 3Dモデルの生成
	Model* model_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	// カメラ
	Camera camera_;

	// 自キャラ
	Player* player_ = nullptr;

	// 敵
	Enemy* enemy_ = nullptr;

	// テクスチャハンドル
	uint32_t enemyTextureHandle_ = 0;

	// 3Dモデルの生成
	Model* enemyModel_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform enemyWorldTransform_;

	// カメラ
	Camera enemyCamera_;

	void CheckAllCollisions();

	// デバッグカメラ
	bool isDebugCameraActive_ = false;

	DebugCamera* debugCamera_ = nullptr;

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

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
