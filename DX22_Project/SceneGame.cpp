#include "SceneGame.h"
#include "Geometory.h"
#include "Defines.h"
#include "CameraDebug.h"
#include "CameraInGame.h"
#include "ShaderList.h"
#include "Spring.h"

Spring* g_spring;

SceneGame::SceneGame()
{
	_camera = new CameraInGame();

	g_spring = new Spring();
	g_spring->SetCamera(_camera);
}

SceneGame::~SceneGame()
{

	if (_camera) {
		delete _camera;
		_camera = nullptr;
	}
}

void SceneGame::Update()
{
	_camera->Update();
	g_spring->Update();
}

void SceneGame::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV(); // RenderTargetView 
	DepthStencil* pDSV = GetDefaultDSV(); // DepthStencilView 
	SetRenderTargets(1, &pRTV, pDSV);

	Geometory::SetView(_camera->GetViewMatrix());
	Geometory::SetProjection(_camera->GetProjectionMatrix());

	g_spring->Draw();
}
