#include <KamataEngine.h>
using namespace KamataEngine;
#include "affine.h"

void WorldTransform::UpdateMatrix() {
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	TransferMatrix();
}