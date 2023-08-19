#pragma once
#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include <cassert>
#include <cmath>
#include <math.h>

/// <summary>
/// 数学系関数クラス
/// </summary>
class MyMath {
public: // メンバ関数
	/// <summary>
	/// ベクトル内積計算関数
	/// </summary>
	/// <param name="v1">ベクトル1</param>
	/// <param name="v2">ベクトル2</param>
	/// <returns>内積</returns>
	static float Dot(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// ベクトル長さ計算関数
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>ベクトル長さ</returns>
	static float Length(const Vector3& v);

	/// <summary>
	/// ベクトル正規化関数
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>正規化ベクトル</returns>
	static Vector3 Normalize(const Vector3& v);

	/// <summary>
	/// ワールド座標変換関数
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <param name="m">4x4行列</param>
	/// <returns>ワールド座標</returns>
	static Vector3 Transform(const Vector3& v, const Matrix4x4& m);

	/// <summary>
	/// 逆行列計算関数
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	static Matrix4x4 Inverse(const Matrix4x4 m);

	/// <summary>
	/// 単位行列生成関数
	/// </summary>
	/// <returns>単位行列</returns>
	static Matrix4x4 MakeIdentity4x4();

	/// <summary>
	/// 平行移動行列生成関数
	/// </summary>
	/// <param name="translate">位置座標</param>
	/// <returns>平行移動行列</returns>
	static Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	/// <summary>
	/// 拡大縮小行列生成関数
	/// </summary>
	/// <param name="scale">拡縮</param>
	/// <returns>拡大縮小行列</returns>
	static Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	/// <summary>
	/// X軸回転行列生成関数
	/// </summary>
	/// <param name="X">回転角度(ラジアン)</param>
	/// <returns>X軸回転行列</returns>
	static Matrix4x4 MakeRotateXMatrix(const float& X);
	/// <summary>
	/// Y軸回転行列生成関数
	/// </summary>
	/// <param name="Y">回転角度(ラジアン)</param>
	/// <returns>Y軸回転行列</returns>
	static Matrix4x4 MakeRotateYMatrix(const float& Y);
	/// <summary>
	/// Z軸回転行列生成関数
	/// </summary>
	/// <param name="Z">回転角度(ラジアン)</param>
	/// <returns>Z軸回転行列</returns>
	static Matrix4x4 MakeRotateZMatrix(const float& Z);

	/// <summary>
	/// 回転行列生成関数
	/// </summary>
	/// <param name="rotate">回転角度(Vector3)(radian)</param>
	/// <returns>回転行列</returns>
	static Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate);

	/// <summary>
	/// アフィン行列生成関数
	/// </summary>
	/// <param name="scale">拡縮</param>
	/// <param name="rotate">回転角</param>
	/// <param name="translate">位置座標</param>
	/// <returns>アフィン行列</returns>
	static Matrix4x4
	    MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

	/// <summary>
	/// 正射影行列生成関数
	/// </summary>
	/// <param name="left">画面左</param>
	/// <param name="top">画面上</param>
	/// <param name="right">画面右</param>
	/// <param name="bottom">画面下</param>
	/// <param name="nearClip">近平面</param>
	/// <param name="farClip">遠平面</param>
	/// <returns>正射影行列</returns>
	static Matrix4x4 MakeOrthGraphicMatrix(
	    const float& left, const float& top, const float& right, const float& bottom,
	    const float& nearClip, const float& farClip);

	/// <summary>
	/// 透視射影行列生成関数
	/// </summary>
	/// <param name="fovY">視野角</param>
	/// <param name="aspectRatio">画面アスペクト比</param>
	/// <param name="nearClip">近平面への距離</param>
	/// <param name="farClip">遠平面への距離</param>
	/// <returns>透視射影行列</returns>
	static Matrix4x4 MakePerspectiveFovMatrix(
	    const float& fovY, const float& aspectRatio, const float& nearClip, const float& farClip);

	/// <summary>
	/// ビューポート変換行列生成関数
	/// </summary>
	/// <param name="left">画面左</param>
	/// <param name="top">画面上</param>
	/// <param name="width">画面横幅</param>
	/// <param name="height">画面縦幅</param>
	/// <param name="minDepth">最低深度</param>
	/// <param name="maxDepth">最大深度</param>
	/// <returns>ビューポート行列</returns>
	static Matrix4x4 MakeViewportMatrix(
	    float left, float top, float width, float height, float minDepth, float maxDepth);
};
