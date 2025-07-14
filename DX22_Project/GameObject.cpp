#include "GameObject.h"
#include "ShaderList.h"
#include "Geometory.h"

void GameObject::Init()
{
}

void GameObject::Uninit()
{
}

void GameObject::Update()
{
}

void GameObject::Draw()
{

	DirectX::XMMATRIX world, S, R, T;
	DirectX::XMFLOAT4X4 wvp[3];

	S = DirectX::XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	R = DirectX::XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	T = DirectX::XMMatrixTranslation(_position.x, _position.y, _position.z);
	world = S * R * T;

	DirectX::XMStoreFloat4x4(&wvp[0], XMMatrixTranspose(world));
	wvp[1] = _camera->GetViewMatrix();
	wvp[2] = _camera->GetProjectionMatrix();

	ShaderList::SetWVP(wvp);

	_model->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
	_model->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));

	for (int i = 0; i < _model->GetMeshNum(); ++i)
	{
		// モデルのメッシュを取得
		Model::Mesh mesh = *_model->GetMesh(i);
		// メッシュに割り当てられているマテリアルを取得
		Model::Material material = *_model->GetMaterial(mesh.materialID);

		// シェーダーへマテリアルを設定
		ShaderList::SetMaterial(material);
		// モデルの描画
		_model->Draw(i);
	}
}
