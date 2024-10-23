#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

//Matrix4x4 MakeScaleMatrix(const Vector3& scale);
//
//Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
//
//Matrix4x4 MakeRotateMatrix(const Vector3& rotate);