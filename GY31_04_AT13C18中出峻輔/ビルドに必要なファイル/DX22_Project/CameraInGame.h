#pragma once
#include "Camera.h"
#include "Ball.h"
class CameraInGame : public Camera
{
public:
	CameraInGame();
	~CameraInGame();

	void Update() override;
	void SetBall(Ball* ball) { _ball = ball; }

private:
	Ball* _ball = nullptr;
};

