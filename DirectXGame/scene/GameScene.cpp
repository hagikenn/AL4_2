#include <KamataEngine.h>
using namespace KamataEngine;
#include "GameScene.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	//3Dモデルデータの解放

	//自キャラの解放
	delete player_;

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

	debugCamera_->Update();

	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
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
