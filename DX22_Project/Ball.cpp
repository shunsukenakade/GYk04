#include "Ball.h"
#include "Defines.h"

Ball::Ball()
{
    _model = new Model();
    if (!_model->Load("Assets/Models/sphere.fbx", 2.0f, Model::None)) {
        MessageBox(NULL, "Assets/Models/sphere.fbx", "Error", MB_OK);
    }
}

void Ball::Update()
{
    if (!_isAttached)
    {

        //_velocity = DirectX::XMVectorScale(_velocity, ATT_COEFFICIENT);	// 抵抗をかける

        DirectX::XMVECTOR gravity = DirectX::XMVectorSet(0.0f, -GRAVITY, 0.0f, 0.0f); // 重力ベクトル
        _velocity = DirectX::XMVectorAdd(_velocity, gravity);	// 重力と弾性力を合成

        DirectX::XMFLOAT3 velocity;	// 計算用にXMFLOAT3に変換
        DirectX::XMStoreFloat3(&velocity, _velocity);

        _position.x += velocity.x;	// x成分
        _position.y += velocity.y;	// y成分
    }
}
