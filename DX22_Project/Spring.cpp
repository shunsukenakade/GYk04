#include "Spring.h"
#include <WinUser.h>
#include "Defines.h"
#include "ShaderList.h"
#include "Input.h"

Spring::Spring()
{
    _model = new Model();
    if (!_model->Load("Assets/Models/sphere.fbx", 1.0f, Model::None)) {
        MessageBox(NULL, "Assets/Models/sphere.fbx", "Error", MB_OK);
    }

	_position.z = -10.0f;
}

void Spring::Update()
{

	// ---マウス操作---
	if (IsKeyPress(VK_LBUTTON)) 
	{
		_ball->SetAttached(true);

		_velocity = { 0.0f, 0.0f, 0.0f }; // マウスを押したときは速度をリセット

		// マウスの位置を取得
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(GetActiveWindow(), &mousePos); // ウィンドウのクライアント座標に変換

		// 中心が0になるように
		float mx = static_cast<float>(mousePos.x - SCREEN_WIDTH / 2);
		float my = static_cast<float>(-(mousePos.y - SCREEN_HEIGHT / 2));

		// ピクセルから3D空間の座標に変換するための係数を計算
		float fovy = _camera->GetFovy();
		float halfHeight = (_endPos.z - _camera->GetPos().z) * tanf(fovy / 2);
		float rate = halfHeight / (SCREEN_HEIGHT / 2);

		_endPos.x = mx * rate + _camera->GetPos().x;
		if(_endPos.x > 48.0f)
		{
			_endPos.x = 48.0f; // x座標の制限
		}
		_endPos.y = my * rate + _camera->GetPos().y;
	}
	else
	{
		// ---ばねの処理---
		_velocity = DirectX::XMVectorScale(_velocity, ATT_COEFFICIENT);	// 抵抗をかける

		DirectX::XMVECTOR start = DirectX::XMLoadFloat3(&_startPos);
		DirectX::XMVECTOR end = DirectX::XMLoadFloat3(&_endPos);

		DirectX::XMVECTOR springForce = DirectX::XMVectorSubtract(start, end);
		DirectX::XMFLOAT3 length;	// 長さを先に保持しておく
		DirectX::XMStoreFloat3(&length, DirectX::XMVector3Length(springForce));

		springForce = DirectX::XMVector3Normalize(springForce); // 単位ベクトルに正規化
		float d = length.x - SPRING_DEFAULT_LENGTH;	// 変位長を求める
		float f = d * SPRING_COEFFICIENT; // 変位長から弾性力を求める
		springForce = DirectX::XMVectorScale(springForce, f);

		DirectX::XMVECTOR gravity = DirectX::XMVectorSet(0.0f, -GRAVITY * BALL_MASS, 0.0f, 0.0f); // 重力ベクトル
		DirectX::XMVECTOR force = DirectX::XMVectorAdd(springForce, gravity);	// 重力と弾性力を合成

		DirectX::XMVECTOR acceleration = DirectX::XMVectorDivide(force, DirectX::XMVectorReplicate(BALL_MASS)); // 加速度を求める
		_velocity = DirectX::XMVectorAdd(_velocity, acceleration); // 速度を更新

		DirectX::XMFLOAT3 velocity;	// 計算用にXMFLOAT3に変換
		DirectX::XMStoreFloat3(&velocity, _velocity);

		_endPos.x += velocity.x;	// x成分
		_endPos.y += velocity.y;	// y成分
	}

	// ---ボールをとばす処理---
	if (_ball->GetAttached())
	{
		_ball->SetPosition(_endPos);
		DirectX::XMFLOAT3 vel;
		DirectX::XMStoreFloat3(&vel, DirectX::XMVector3Length(_velocity));
		if (vel.x > 10.0f)
		{
			_ball->SetAttached(false); // 速度が大きくなったらボールを離す
			_ball->SetVelocity(_velocity);
		}
	}

}

void Spring::Draw()
{
	if (!_model || !_camera)
	{
		return;
	}

	DirectX::XMMATRIX world, S, R, T;
	DirectX::XMFLOAT4X4 wvp[3];

	wvp[1] = _camera->GetViewMatrix();
	wvp[2] = _camera->GetProjectionMatrix();


	_model->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
	_model->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));

	for (int i = 0; i < 10; ++i)
	{
		float t = i / 9.0f;

		S = DirectX::XMMatrixScaling(_scale.x, _scale.y, _scale.z);
		R = DirectX::XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
		T = DirectX::XMMatrixTranslation(
			_startPos.x + (_endPos.x - _startPos.x) * t,
			_startPos.y + (_endPos.y - _startPos.y) * t,
			_startPos.z + (_endPos.z - _startPos.z) * t);
		world = S * R * T;

		DirectX::XMStoreFloat4x4(&wvp[0], XMMatrixTranspose(world));
		ShaderList::SetWVP(wvp);

		_model->Draw();
	}
}
