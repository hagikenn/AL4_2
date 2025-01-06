#include "GameScene.h"
#include <cassert>
#include <math.h>

#include <KamataEngine.h>
using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	// 自キャラの開放
	delete model_;
	delete player_;
	// delete debugCamera_;
	delete enemy_;
	delete modelDeathParticle_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// ファイル名を指定してテクスチャを読み込む
	// textureHandle_ = TextureManager::Load("mario.jpg");

	bulletText_ = TextureManager::Load("black1x1.png");

	// モデル
	model_ = Model::CreateFromOBJ("player");

	// ワールドトランスフォーム
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// 天球
	modelSkyDome_ = Model::CreateFromOBJ("skyDome", true);
	skyDome_ = new Skydome();
	skyDome_->Initialize(modelSkyDome_, &viewProjection_);

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化

	player_->Initialize(model_ /*, &viewProjection_*/, worldTransform_.translation_);

	GameScene::HP = 3;
	GameScene::enemyHP = 7;

	// 敵の生成
	enemy_ = new Enemy();
	// 敵の初期化
	enemy_->Initialize(model_);
	// const uint32_t kNumBlockVirtical = 20;
	// const uint32_t kNumBlockHorizontal = 100;

	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

	modelDeathParticle_ = Model::CreateFromOBJ("DeathParticle", true);

	playerLifeTexture3_ = TextureManager::Load("playerLife/3.png");
	sprite3_ = Sprite::Create(playerLifeTexture3_, {0, 0});

	playerLifeTexture2_ = TextureManager::Load("playerLife/2.png");
	sprite2_ = Sprite::Create(playerLifeTexture2_, {0, 0});

	playerLifeTexture1_ = TextureManager::Load("playerLife/1.png");
	sprite1_ = Sprite::Create(playerLifeTexture1_, {0, 0});

	playerLifeTexture0_ = TextureManager::Load("playerLife/0.png");
	sprite0_ = Sprite::Create(playerLifeTexture0_, {0, 0});

	enemyLifeTexture7_ = TextureManager::Load("bossLife/7.png");
	enemySprite7_ = Sprite::Create(enemyLifeTexture7_, {0, 0});

	enemyLifeTexture6_ = TextureManager::Load("bossLife/6.png");
	enemySprite6_ = Sprite::Create(enemyLifeTexture6_, {0, 0});

	enemyLifeTexture5_ = TextureManager::Load("bossLife/5.png");
	enemySprite5_ = Sprite::Create(enemyLifeTexture5_, {0, 0});

	enemyLifeTexture4_ = TextureManager::Load("bossLife/4.png");
	enemySprite4_ = Sprite::Create(enemyLifeTexture4_, {0, 0});

	enemyLifeTexture3_ = TextureManager::Load("bossLife/3.png");
	enemySprite3_ = Sprite::Create(enemyLifeTexture3_, {0, 0});

	enemyLifeTexture2_ = TextureManager::Load("bossLife/2.png");
	enemySprite2_ = Sprite::Create(enemyLifeTexture2_, {0, 0});

	enemyLifeTexture1_ = TextureManager::Load("bossLife/1.png");
	enemySprite1_ = Sprite::Create(enemyLifeTexture1_, {0, 0});

	enemyLifeTexture0_ = TextureManager::Load("bossLife/0.png");
	enemySprite0_ = Sprite::Create(enemyLifeTexture0_, {0, 0});

	// デバッグカメラの生成
	// debugCamera_ = new DebugCamera(kNumBlockHorizontal, kNumBlockVirtical);

	// 軸方向
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(&viewProjection_);

	// サウンドデータの読み込み
	soundDataHandle_ = audio_->LoadWave("Boss.wav");
	// 音声再生
	audio_->PauseWave(soundDataHandle_);
	// 第2引数でループ再生を指定
	voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);
}

void GameScene::Update() {

	bossTimer += 1;

	skyDome_->Update();

	if (bossTimer < 100) {
		return;
	}
	player_->Update();
	enemy_->Update();

	if (enemy_->IsDead() == true) {
	}
	if (player_->IsDead() == true) {
	}

	/*#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
	    isDebugCameraActive_ = !isDebugCameraActive_;
	}
	#endif*/

	// if (isDebugCameraActive_) {
	//	//debugCamera_->Update();
	//	viewProjection_.matView = debugCamera_->GetCamera().matView;
	//	viewProjection_.matProjection = debugCamera_->GetCamera().matProjection;
	//	viewProjection_.TransferMatrix();
	// } else {
	//	viewProjection_.UpdateMatrix();
	// }

	// 自機の弾が敵に当たったとき
	std::list<PlayerBullet*> playerBullets = player_->GetBullet();
	for (PlayerBullet* playerBullet : playerBullets) {
		Vector3 enemyPosition = enemy_->GetPosition();
		Vector3 playerBulletPosition = playerBullet->GetPosition();
		if (abs(playerBulletPosition.x - enemyPosition.x) < 3 && abs(playerBulletPosition.y - enemyPosition.y) < 3 && abs(playerBulletPosition.z - enemyPosition.z) < 3) {
			// player_->OnCollision(enemy_);
			playerBullet->OnCollision();
			enemy_->OnCollision(player_);
			// 仮の生成処理。後で消す
			deathParticles_ = new DeathParticles;
			deathParticles_->Initialize(modelDeathParticle_, &viewProjection_, worldTransform_.translation_);
			enemyHP -= 1;
		}
	}

	// 敵の弾が自機に当たったとき
	std::list<EnemyBullet*> enemyBullets = enemy_->GetBullet();
	for (EnemyBullet* enemyBullet : enemyBullets) {
		Vector3 playerPosition = player_->GetPosition();
		Vector3 enemyBulletPosition = enemyBullet->GetPosition();
		if (abs(enemyBulletPosition.x - playerPosition.x) < 3 && abs(enemyBulletPosition.y - playerPosition.y) < 3 && abs(enemyBulletPosition.z - playerPosition.z) < 3) {
			// enemy_->OnCollision(player_);
			enemyBullet->OnCollision();
			player_->OnCollision(enemy_);

			HP -= 1;
			// 仮の生成処理。後で消す
			/*deathParticles_ = new DeathParticles;
			deathParticles_->Initialize(modelDeathParticle_, &viewProjection_, worldTransform_.translation_);*/
		}
	}

	// パーティクルの更新
	if (deathParticles_) {
		deathParticles_->Update();
	}

	if (enemy_->IsFinished()) {
		EnemyFinished_ = true;
	}

	if (player_->IsFinished()) {
		PlayerFinished_ = true;
	}

	if (HP <= 0 || enemyHP <= 0) {
		// 音声停止
		audio_->StopWave(voiceHandle_);
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 天球
	skyDome_->Draw(viewProjection_);

	// 自キャラの描画
	player_->Draw(viewProjection_);
	// 敵の描画
	enemy_->Draw(viewProjection_);

	// パーティクルの描画
	if (deathParticles_) {
		deathParticles_->Draw();
	}

	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	if (HP == 3) {
		sprite3_->Draw();
	}

	if (HP == 2) {
		sprite2_->Draw();
	}

	if (HP == 1) {
		sprite1_->Draw();
	}

	if (HP <= 0) {
		sprite0_->Draw();
	}

	if (enemyHP == 7) {
		enemySprite7_->Draw();
	}

	if (enemyHP == 6) {
		enemySprite6_->Draw();
	}

	if (enemyHP == 5) {
		enemySprite5_->Draw();
	}

	if (enemyHP == 4) {
		enemySprite4_->Draw();
	}

	if (enemyHP == 3) {
		enemySprite3_->Draw();
	}

	if (enemyHP == 2) {
		enemySprite2_->Draw();
	}

	if (enemyHP == 1) {
		enemySprite1_->Draw();
	}

	if (enemyHP <= 0) {
		enemySprite0_->Draw();
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
