#include "Spring.h"
#include <WinUser.h>
#include "Defines.h"
#include "ShaderList.h"

Spring::Spring()
{
    _model = new Model();
    if (!_model->Load("Assets/Models/sphere.fbx", 1.0f, Model::None)) {
        MessageBox(NULL, "Assets/Models/sphere.fbx", "Error", MB_OK);
    }

	_texture = new Texture();
	if (FAILED(_texture->Create("Assets/Texture/arrow.jpg"))) {
		MessageBox(NULL, "Assets/Texture/arrow.jpg", "Error", MB_OK);
	}

	_position.z = -10.0f;
}

void Spring::Update()
{
	// ---マウス操作---
	
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
	_endPos.y = my * rate + _camera->GetPos().y;


	// ---ばねの処理---
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
