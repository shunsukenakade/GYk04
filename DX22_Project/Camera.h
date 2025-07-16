#pragma once
#include <DirectXMath.h>

class Camera {
public:
	// コンストラクタ
	Camera();
	// デストラクタ
	virtual ~Camera();
	// 更新処理(継承先のクラスで必ず実装
	virtual void Update() = 0;
	// ビュー行列の取得（デフォルトでは転置済みの行列を計算する
	DirectX::XMFLOAT4X4 GetViewMatrix(bool transpose = true);
	// プロジェクション行列の取得(デフォルトでは転置済みの行列を計算する)
	DirectX::XMFLOAT4X4 GetProjectionMatrix(bool transpose = true);
	// 座標の取得
	DirectX::XMFLOAT3 GetPos() { return _pos; }
	// 注視点の取得
	DirectX::XMFLOAT3 GetLook() { return _look; }

	float GetFovy() { return _fovy; }		// 画角の取得
	float GetAspect() { return _aspect; }	// アスペクト比の取得

	void SetLook(DirectX::XMFLOAT3 look) { _look = look; }

protected:
	DirectX::XMFLOAT3 _pos;	// 座標
	DirectX::XMFLOAT3 _look;	// 注視点
	DirectX::XMFLOAT3 _up;		// 上方ベクトル
	float	_fovy;				// 画角
	float	_aspect;			// アスペクト比
	float	_near;				// ニアクリップ
	float	_far;				// ファークリップ
};