#include "TitleScene.h"
#include <numbers>

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {
	delete modelFont_;
	delete modelEnemy_;
	delete fade_;
	finished_ = false;
}

void TitleScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ビュープロジェクション
	camera_.Initialize();

	modelFont_ = Model::CreateFromOBJ("titleFont");
	modelEnemy_ = Model::CreateFromOBJ("enemyOpposition");

	worldTransformFont_.Initialize();
	worldTransformPlayer_.Initialize();

	worldTransformFont_.translation_.y = 10;
	worldTransformPlayer_.translation_.y = -11;
	worldTransformFont_.scale_ = {2, 2, 2};
	worldTransformPlayer_.scale_ = {2, 2, 2};
	worldTransformPlayer_.rotation_.y = std::numbers::pi_v<float>;

	// フェード
	phase_ = Phase::kFadeIn;
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1);

	// サウンドデータの読み込み
	soundDataHandle_ = audio_->LoadWave("Title.wav");
	// 音声再生
	audio_->PauseWave(soundDataHandle_);
	// 第2引数でループ再生を指定
	voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);
}

void TitleScene::Update() {

	// SPACEキーを押すとフェードアウトを開始
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		if (phase_ != Phase::kFadeOut) {
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1);
		}
	}

	// フェードアウトが終了したらゲームシーンに行く
	if (fade_->IsFadeOutFinished() == true) {
		// 音声停止
		audio_->StopWave(voiceHandle_);
		finished_ = true;
	}

	// タイマーを加算
	timer_ += 1.0f / 60.0f;

	// 行列を更新
	worldTransformFont_.UpdateMatrix();
	worldTransformPlayer_.UpdateMatrix();

	// フェード
	fade_->Update();
}

void TitleScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	// ここに3Dオブジェクトの描画処理を追加できる
	modelFont_->Draw(worldTransformFont_, camera_);
	modelEnemy_->Draw(worldTransformPlayer_, camera_);

	// 3Dオブジェクト描画処理後
	Model::PostDraw();

	// フェード
	fade_->Draw(commandList);
}
