#include "CameraInGame.h"

CameraInGame::CameraInGame()
{
	_pos = { 50.0f, 0.0f, -100.0f };
	_look = { 50.0f, 0.0f, 0.0f };
}

CameraInGame::~CameraInGame()
{
}

void CameraInGame::Update()
{
	//if (!_ball->GetAttached())
	//{
	//	_pos = _ball->GetPosition();
	//	_pos.y = 0.0f;
	//	_pos.z -= 100.0f;

	//	_look = _ball->GetPosition();
	//	_look.y = 0.0f;
	//}
	//else
	//{
	//	_pos = { 0.0f, 0.0f, -100.0f };
	//	_look = { 0.0f, 0.0f, 0.0f };
	//}
}
