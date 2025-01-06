#include "Player.h"
#include "MathUtilityForText.h"
#include <cassert>

Player::~Player() { delete bullet_; }

void Player::Initialize(Model* model, const KamataEngine::Vector3& position) {
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	// NULLポインタをチェックする
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	// textureHandle_ = textureHandle;

	worldTransform_.translation_ = position;
	// ワールド変換の初期化
	worldTransform_.Initialize();

	audio_ = Audio::GetInstance();
	soundDataHandle_ = audio_->LoadWave("playerShot.wav");
}

void Player::Update() {
	worldTransform_.UpdateMatrix();
	// model_ = Model::CreateFromOBJ("enemy");
	//  行列更新
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.7f;

	// デスフラグのたった弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// 押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT) || input_->PushKey(DIK_A)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT) || input_->PushKey(DIK_D)) {
		move.x += kCharacterSpeed;
	}

	// 押した方向で移動ベクトルを変更（上下）
	if (input_->PushKey(DIK_DOWN) || input_->PushKey(DIK_S)) {
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_UP) || input_->PushKey(DIK_W)) {
		move.y += kCharacterSpeed;
	}

	// 座標移動（ベクトルの加算）
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;

	// ImGui::Begin("Debug1");
	////flo
	// ImGui::InputFloat3("InputFloat3", &worldTransform_.translation_.x);
	// ImGui::SliderFloat3("SliderFloat3", &worldTransform_.translation_.x, -10.0f, 10.0f);
	// ImGui::End();

	// 移動限界座標
	const float kMoveLimitX = 35;
	const float kMoveLimitY = 19;

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	// キャラクター攻撃処理
	Attack();

	// 旋回
	Rotate();

	// 弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Player::Draw(Camera& camera) {
	if (Life == true) {
		model_->Draw(worldTransform_, camera);
	}

	// 弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(camera);
	}
}

void Player::Rotate() {
	//-----------追加-------------//

	//// 回転速さ[ラジアン/frame]
	// const float kRotSpeed = 0.1f;

	//// 押した方向で移動ベクトルを変更
	// if (input_->PushKey(DIK_Q)) {
	//	worldTransform_.rotation_.y -= kRotSpeed;
	// } else if (input_->PushKey(DIK_E)) {
	//	worldTransform_.rotation_.y += kRotSpeed;
	// }

	//---------------------------//
}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		// 弾があれば開放する
		if (bullet_) {
			delete bullet_;
			bullet_ = nullptr;
		}

		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);

		audio_->PlayWave(soundDataHandle_);
	}
}

Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Player::OnCollision(const Enemy* enemy) {
	(void)enemy;
	/*  isDead_ = true;
	  finished_ = true;
	  Life = false;*/
}

void Player::OnCollision(const MobEnemy* mobEnemy) {
	(void)mobEnemy;
	isDead_ = true;
	finished_ = true;
	Life = false;
}
