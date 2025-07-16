#pragma once
#include <DirectXMath.h>
#include <Model.h>
#include "Camera.h"

class GameObject
{
protected:
	// 位置、回転、回転情報
	DirectX::XMFLOAT3 _position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT3 _rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT3 _scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);

	Model* _model = nullptr; // モデルへのポインタ
	Camera* _camera = nullptr; // カメラへのポインタ
public:
	GameObject() {}
	~GameObject() {}

	// Getter　変数を公開すると後々
	DirectX::XMFLOAT3 GetPosition() { return _position; }
	DirectX::XMFLOAT3 GetRotation() { return _rotation; }
	DirectX::XMFLOAT3 GetScale() { return _scale; }
	// Setter
	void SetPosition(DirectX::XMFLOAT3 pos) { _position = pos; }
	void SetRotation(DirectX::XMFLOAT3 rot) { _rotation = rot; }
	void SetScale(DirectX::XMFLOAT3 scale) { _scale = scale; }
	void SetCamera(Camera* camera) { _camera = camera; }
	// 仮想関数
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
};

