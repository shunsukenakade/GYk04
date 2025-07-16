#include "SceneGame.h"
#include "Geometory.h"
#include "Defines.h"
#include "CameraDebug.h"
#include "CameraInGame.h"
#include "ShaderList.h"
#include "Spring.h"
#include "Ball.h"
#include "Goal.h"

Spring* g_spring;
Ball* g_ball;
Goal* g_goal;

SceneGame::SceneGame()
{
	CameraInGame* cameraInGame = new CameraInGame();

	g_spring = new Spring();
	g_ball = new Ball();
	g_goal = new Goal();

	cameraInGame->SetBall(g_ball);
	g_spring->SetBall(g_ball);

	_camera = cameraInGame;

	g_spring->SetCamera(_camera);
	g_ball->SetCamera(_camera);
	g_goal->SetCamera(_camera);

}

SceneGame::~SceneGame()
{
	if (g_goal) {
		delete g_goal;
		g_goal = nullptr;
	}
	if (g_ball) {
		delete g_ball;
		g_ball = nullptr;
	}
	if (g_spring) {
		delete g_spring;
		g_spring = nullptr;
	}
	if (_camera) {
		delete _camera;
		_camera = nullptr;
	}
}

void SceneGame::Update()
{
	_camera->Update();
	g_spring->Update();
	g_ball->Update();
	g_goal->Update();

	g_goal->CheckCollision(g_ball);
}

void SceneGame::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV(); // RenderTargetView 
	DepthStencil* pDSV = GetDefaultDSV(); // DepthStencilView 
	SetRenderTargets(1, &pRTV, pDSV);

	Geometory::SetView(_camera->GetViewMatrix());
	Geometory::SetProjection(_camera->GetProjectionMatrix());

	g_spring->Draw();
	g_ball->Draw();
	g_goal->Draw();
}
