#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

struct AABB {
	Vector3 min; // 最小点
	Vector3 max; // 最大点

	static bool IsCollision(const AABB& aabb1, const AABB& aabb2);
};