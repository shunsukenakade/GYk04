#pragma once
#include "GameObject.h"
class Spring : public GameObject
{
public:
	Spring();

	void Update() override;
	void Draw() override;

private:
	DirectX::XMFLOAT3 _startPos = { 0.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT3 _endPos = { 0.0f, 0.0f, 0.0f };
	
	Texture* _texture;
};

