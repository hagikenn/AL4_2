
#include "GameScene.h"
#include "../MathUtilityForText.h"
#include <cassert>
using namespace MathUtility;


GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete enemy_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 軸方向の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetCamera(&debugCamera_->GetCamera());

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	// 3Dモデルの生成
	model_ = Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// カメラの初期化
	camera_.Initialize();

	// 天球
	modelSkyDome_ = Model::CreateFromOBJ("skyDome", true);
	skyDome_ = new Skydome();
	skyDome_->Initialize(modelSkyDome_, &camera_);


	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_);

	// 敵のテクスチャ
	enemyTextureHandle_ = TextureManager::Load("enemy.png");

	// 敵のモデル
	enemyModel_ = Model::Create();

	// 敵のワールドトランスフォームの初期化
	enemyWorldTransform_.Initialize();

	// 敵のカメラの初期化
	enemyCamera_.Initialize();

	// 敵キャラの生成
	enemy_ = new Enemy;

	// 敵キャラの初期化
	enemy_->Initialize(enemyModel_, enemyTextureHandle_);

	enemy_->SetPlayer(player_);

}

void GameScene::CheckAllCollisions() {

	// 判定AとBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<PlayerBullet*> playerBullets = player_->GetBullets();
	// 敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

#pragma region
	posA = player_->GetWorldPosition();
	for (EnemyBullet* bullet : enemyBullets) {

		posB = bullet->GetWorldPosition();

		Vector3 subtract = posB - posA;

		float a = Length(subtract);

		if (a < 3.0f) {

			player_->OnCollision();
			bullet->OnCollision();
		}
	}

#pragma endregion

#pragma region

	posA = enemy_->GetWorldPosition();
	for (PlayerBullet* bullet : playerBullets) {

		posB = bullet->GetWorldPosition();

		Vector3 subtract = posB - posA;

		float a = Length(subtract);

		if (a < 3.0f) {

			enemy_->OnCollision();
			bullet->OnCollision();
		}
	}

#pragma endregion

#pragma region

	for (PlayerBullet* pBullet : playerBullets) {
		for (EnemyBullet* eBullet : enemyBullets) {

			posA = pBullet->GetWorldPosition();
			posB = eBullet->GetWorldPosition();

			Vector3 subtract = posB - posA;

			float a = Length(subtract);

			if (a < 3.0f) {
				pBullet->OnCollision();
				eBullet->OnCollision();
			}
		}
	}
#pragma endregion
}

void GameScene::Update() {

	// デバッグカメラの更新
	debugCamera_->Update();

	skyDome_->Update();


#ifdef _DEBUG

	if (input_->TriggerKey(DIK_RETURN)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}

#endif //  _DEBUG

	if (isDebugCameraActive_) {

		debugCamera_->Update();

		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		camera_.TransferMatrix();
	} else {
		camera_.UpdateMatrix();
	}

	// 自キャラの更新
	player_->Update();

	// 敵キャラの更新
	enemy_->Update();

	CheckAllCollisions();
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

	// 3Dモデル描画
	// model_->Draw(worldTransform_, camera_, textureHandle_);

	// 天球
	skyDome_->Draw(camera_);

	// 自キャラの描画
	if (isDebugCameraActive_ == false) {
		player_->Draw(camera_);
	}

	if (isDebugCameraActive_) {
		model_->Draw(worldTransform_, debugCamera_->GetCamera(), textureHandle_);
	}

	enemy_->Draw(enemyCamera_);

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
