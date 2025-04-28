#include "SceneGame.h"
#include "Geometory.h"
#include "Defines.h"
#include "CameraDebug.h"
#include "ShaderList.h"

SceneGame::SceneGame()
{
	m_pCamera = new CameraDebug();

	m_pModel = new Model();
	if (!m_pModel->Load("Models/FBX_Demo_standing.fbx")) {
		MessageBox(NULL, "Models/FBX_Demo_standing.fbx", "Error", MB_OK);
	}
}

SceneGame::~SceneGame()
{
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
}

void SceneGame::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);

	DirectX::XMMATRIX T;	// 移動行列
	DirectX::XMMATRIX Rx;	// X軸回転行列
	DirectX::XMMATRIX Ry;	// Y軸回転行列
	DirectX::XMMATRIX Rz;	// Z軸回転行列
	DirectX::XMMATRIX S;	// 拡大縮小行列
	DirectX::XMMATRIX mat;
	DirectX::XMFLOAT4X4 fMat;	// 行列の格納先
	DirectX::XMFLOAT4X4 wvp[3];
	DirectX::XMMATRIX world, view, proj;

	// 変換行列作成
	T = DirectX::XMMatrixTranslation(METER(0.0f), METER(0.0f), METER(0.0f));// 移動行列
	Rx = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(0.0f));// X軸回転行列
	Ry = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(0.0f));// Y軸回転行列
	Rz = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(0.0f));// Z軸回転行列
	S = DirectX::XMMatrixScaling(METER(1.0f), METER(1.0f), METER(1.0f));// 拡大縮小行列
	world = S * Rx * Ry * Rz * T;

	// 計算用のデータから読み取り用のデータに変換
	DirectX::XMStoreFloat4x4(&wvp[0], XMMatrixTranspose(world));
	wvp[1] = m_pCamera->GetViewMatrix();
	wvp[2] = m_pCamera->GetProjectionMatrix();

	Geometory::SetView(wvp[1]);
	Geometory::SetProjection(wvp[2]);

	// シェーダーへ変換行列を設定
	ShaderList::SetWVP(wvp);	// 引数にはXMFLOAT4X4型の、要素数3の配列アドレスを渡す

	// モデルに仕様する頂点シェーダー、ピクセルシェーダーを設定
	m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
	m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));

	// 複数のメッシュで構成されている場合、ある部分は金属的な表現、ある部分は非金属的な表現と
	// 分ける場合がある。前回の表示は同じマテリアルで一括表示していたため、メッシュ事にマテリアルを
	// 切り替える。
	for (int i = 0; i < m_pModel->GetMeshNum(); ++i)
	{
		// モデルのメッシュを取得
		Model::Mesh mesh = *m_pModel->GetMesh(i);
		// メッシュに割り当てられているマテリアルを取得
		Model::Material material = *m_pModel->GetMaterial(mesh.materialID);
		// シェーダーへマテリアルを設定
		ShaderList::SetMaterial(material);
		// モデルの描画
		m_pModel->Draw(i);
	}

	// Geometory::DrawBox();
}
