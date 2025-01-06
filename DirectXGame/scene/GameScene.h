#pragma once

#include <KamataEngine.h>
using namespace KamataEngine;
//#include "DeathParticles.h"
#include "../Enemy.h"
#include "../EnemyBullet.h"
#include "../Player.h"
#include "../Player.h"
#include "../PlayerBullet.h"
#include "../Skydome.h"

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

	int HP;
	int enemyHP;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	bool isDebugCameraActive_ = false;

	// デスフラグのgetter
	bool PlayerIsFinished() const { return PlayerFinished_; }
	bool EnemyIsFinished() const { return EnemyFinished_; }

	// 天球
	Skydome* skyDome_ = nullptr;
	Model* modelSkyDome_ = nullptr;

private: // メンバ変数
	// 終了フラグ
	bool PlayerFinished_ = false;

	bool EnemyFinished_ = false;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	// 自キャラ
	Player* player_ = nullptr;
	// 弾
	PlayerBullet* playerBullet_ = nullptr;

	// ボスが現れるまでの時間
	int bossTimer = 0;

	// サウドデータハンドル
	uint32_t soundDataHandle_ = 0;
	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;

	// UI
	uint32_t playerLifeTexture3_ = 0;
	uint32_t playerLifeTexture2_ = 0;
	uint32_t playerLifeTexture1_ = 0;
	uint32_t playerLifeTexture0_ = 0;
	Sprite* sprite3_ = nullptr;
	Sprite* sprite2_ = nullptr;
	Sprite* sprite1_ = nullptr;
	Sprite* sprite0_ = nullptr;

	// 弾
	EnemyBullet* enemyBullet_ = nullptr;
	// 敵
	Enemy* enemy_ = nullptr;

	// UI
	uint32_t enemyLifeTexture7_ = 0;
	uint32_t enemyLifeTexture6_ = 0;
	uint32_t enemyLifeTexture5_ = 0;
	uint32_t enemyLifeTexture4_ = 0;
	uint32_t enemyLifeTexture3_ = 0;
	uint32_t enemyLifeTexture2_ = 0;
	uint32_t enemyLifeTexture1_ = 0;
	uint32_t enemyLifeTexture0_ = 0;
	Sprite* enemySprite7_ = nullptr;
	Sprite* enemySprite6_ = nullptr;
	Sprite* enemySprite5_ = nullptr;
	Sprite* enemySprite4_ = nullptr;
	Sprite* enemySprite3_ = nullptr;
	Sprite* enemySprite2_ = nullptr;
	Sprite* enemySprite1_ = nullptr;
	Sprite* enemySprite0_ = nullptr;

	// int enemyHP = 7;

	// プレイヤーのモデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	uint32_t bulletText_ = 0;

	WorldTransform worldTransform_;
	// ビュープロジェクション
	Camera viewProjection_;
	// デバッグカメラ
	// DebugCamera* debugCamera_ = nullptr;

	// パーティクル
	//DeathParticles* deathParticles_ = nullptr;
	Model* modelDeathParticle_ = nullptr;

	// 弾
	// PlayerBullet* bullet_ = nullptr;

	//std::list<DeathParticles*> deathPartiy_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
