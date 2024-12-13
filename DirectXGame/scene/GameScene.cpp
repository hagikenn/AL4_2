#include <KamataEngine.h>
using namespace KamataEngine;
#include "GameScene.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	//3Dモデルデータの解放

	//自キャラの解放
	delete player_;
	delete enemy_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");

	//3Dモデルデータの生成
	model_ = Model::Create();

	worldTransform_.Initialize();

	//ビュープロジェクションの初期化
	camera_.Initialize();

	//自キャラの生成
	player_ = new Player();
	//自キャラの初期化
	player_->Initialize(model_,textureHandle_);

	// 敵キャラの生成
	enemy_ = new Enemy();
	// 敵キャラの初期化
	enemy_->Initialize(model_, textureHandle_);
	//敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

	//デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	//軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetCamera(&camera_);

}

void GameScene::Update() {
	//自キャラの更新
	player_->Update();
	//敵キャラの更新
	enemy_->Update();

	debugCamera_->Update();

	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0)) {
		if (isDebugCameraActive_ == true) {

			isDebugCameraActive_ = false;

		} else {
			isDebugCameraActive_ = true;
		}
	}
	#endif
	if (isDebugCameraActive_) {
	debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
	camera_.matProjection = debugCamera_->GetCamera().matProjection;
		camera_.TransferMatrix();
	}else {
		camera_.UpdateMatrix();
	}

	// 自機の弾が敵に当たったとき
	std::list<PlayerBullet*> playerBullets = player_->GetBullet();
	for (PlayerBullet* playerBullet : playerBullets) {
		Vector3 enemyPosition = enemy_->GetPosition();
		Vector3 playerBulletPosition = playerBullet->GetPosition();
		if (abs(playerBulletPosition.x - enemyPosition.x) < 3 && abs(playerBulletPosition.y - enemyPosition.y) < 3 && abs(playerBulletPosition.z - enemyPosition.z) < 3) {
			player_->OnCollision(enemy_);
			playerBullet->OnCollision();
			enemy_->OnCollision(player_);
			// 仮の生成処理。後で消す
			
		}
	}

	// 敵の弾が自機に当たったとき
	std::list<EnemyBullet*> enemyBullets = enemy_->GetBullet();
	for (EnemyBullet* enemyBullet : enemyBullets) {
		Vector3 playerPosition = player_->GetPosition();
		Vector3 enemyBulletPosition = enemyBullet->GetPosition();
		if (abs(enemyBulletPosition.x - playerPosition.x) < 3 && abs(enemyBulletPosition.y - playerPosition.y) < 3 && abs(enemyBulletPosition.z - playerPosition.z) < 3) {
			 enemy_->OnCollision(player_);
			enemyBullet->OnCollision();
			player_->OnCollision(enemy_);
		}
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

	//自キャラの描画
	player_->Draw(camera_);
	//敵キャラの描画
	enemy_->Draw(camera_);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

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

//void GameScene::CheckAllCollisions() {
//	//判定対象AとBの座標
//	Vector3 posA, posB;
//
//	//自弾リストの取得
//	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
//	//敵弾リストの取得
//	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();
//
//	#pragma region 自キャラと敵弾の当たり判定
//	//自キャラの座標
//	posA = player_->GetWorldPosition();
//
//	////自キャラと敵弾全ての当たり判定
//	//for (EnemyBullet* bullet : enemyBullets) {
//	//	//敵の座標
//	//	posB=
//	//}
//
//	#pragma endregion
//
//	#pragma region 自弾と敵キャラの当たり判定
//	#pragma endregion
//
//	#pragma region 自弾と敵弾の当たり判定
//	#pragma endregion
//
//}
