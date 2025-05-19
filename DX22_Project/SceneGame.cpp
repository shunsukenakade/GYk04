#include "SceneGame.h"
#include "Geometory.h"
#include "Defines.h"
#include "CameraDebug.h"
#include "ShaderList.h"

#include "Hadouken.h"

SceneGame::SceneGame()
{
	m_pCamera = new CameraDebug();

	m_pModel = new Model();
	if (!m_pModel->Load("Models/FBX_Demo_standing.fbx")) {
		MessageBox(NULL, "Models/FBX_Demo_standing.fbx", "Error", MB_OK);
	}

	m_pCommand = new Command();
	Hadouken* hadou = new Hadouken();
	m_pCommand->SetAction(hadou);
}

SceneGame::~SceneGame()
{
	if (m_pCommand) {
		delete m_pCommand;
		m_pCommand = nullptr;
	}

	if (m_pModel) {
		delete m_pModel;
		m_pModel = nullptr;
	}

	if (m_pCamera) {
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}

void SceneGame::Update()
{
	m_pCamera->Update();
	m_pCommand->Update();
}

void SceneGame::Draw()
{
	m_pCommand->Draw();
}
