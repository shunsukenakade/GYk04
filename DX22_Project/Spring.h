#pragma once
#include "GameObject.h"
#include "Ball.h"

#define SPRING_DEFAULT_LENGTH	5.0f	// ばねの自然長
#define SPRING_COEFFICIENT		1.0f	// ばね係数

class Spring : public GameObject
{
public:
	Spring();

	void Update() override;
	void Draw() override;

	void SetBall(Ball* ball) { _ball = ball; }

private:
	DirectX::XMFLOAT3 _startPos = { 0.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT3 _endPos = { 0.0f, -SPRING_DEFAULT_LENGTH, 0.0f };

	DirectX::XMVECTOR _velocity = { 0.0f, 0.0f, 0.0f };
	
	Ball* _ball = nullptr;	// ばねの先端に接続されているボール
};

