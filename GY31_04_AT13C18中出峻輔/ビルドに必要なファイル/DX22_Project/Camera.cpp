#include "Camera.h"
#include <Defines.h>

Camera::Camera()
	: _pos{ 0.0f, 0.0f, -10.0f }, _look(0.0f, 0.0f, 0.0f), _up(0.0f, 1.0f, 0.0f)
	, _fovy(DirectX::XMConvertToRadians(60.0f)), _aspect(16.0f / 9.0f)
	, _near(CMETER(30.0f)), _far(METER(1000.0f))
{
}

Camera::~Camera()
{
}

DirectX::XMFLOAT4X4 Camera::GetViewMatrix(bool transpose)
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	// ビュー変換行列
	view = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(_pos.x, _pos.y, _pos.z, 0.0f),
		DirectX::XMVectorSet(_look.x, _look.y, _look.z, 0.0f),
		DirectX::XMVectorSet(_up.x, _up.y, _up.z, 0.0f)
	);
	// 転置
	if (transpose)
	{
		view = DirectX::XMMatrixTranspose(view);
	}
	DirectX::XMStoreFloat4x4(&mat, view);
	return mat;
}

DirectX::XMFLOAT4X4 Camera::GetProjectionMatrix(bool transpose)
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;
	// プロジェクション変換行列
	proj = DirectX::XMMatrixPerspectiveFovLH(_fovy, _aspect, _near, _far);
	// 転置
	if (transpose)
	{
		proj = DirectX::XMMatrixTranspose(proj);
	}
	DirectX::XMStoreFloat4x4(&mat, proj);
	return mat;
}
