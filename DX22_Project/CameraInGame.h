#pragma once
#include "Camera.h"
class CameraInGame : public Camera
{
public:
	CameraInGame();
	~CameraInGame();

	void Update() override;
};

