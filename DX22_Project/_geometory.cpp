#include "Geometory.h"

void Geometory::MakeBox()
{
	Vertex vtx[] = {
		// -Z
		{{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f}},
		{{ 0.5f, 0.5f, -0.5f}, {1.0f, 0.0f}},
		{{-0.5f,-0.5f, -0.5f}, {0.0f, 1.0f}},
		{{ 0.5f,-0.5f, -0.5f}, {1.0f, 1.0f}},
		//  Y
		{{-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f}},
		{{ 0.5f, 0.5f,  0.5f}, {1.0f, 0.0f}},
		{{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}},
		{{ 0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
		//  X
		{{ 0.5f, 0.5f, -0.5f}, {0.0f, 0.0f}},
		{{ 0.5f, 0.5f,  0.5f}, {1.0f, 0.0f}},
		{{ 0.5f,-0.5f, -0.5f}, {0.0f, 1.0f}},
		{{ 0.5f,-0.5f,  0.5f}, {1.0f, 1.0f}},
		// -Y
		{{ 0.5f,-0.5f,  0.5f}, {0.0f, 0.0f}},
		{{-0.5f,-0.5f,  0.5f}, {1.0f, 0.0f}},
		{{ 0.5f,-0.5f, -0.5f}, {0.0f, 1.0f}},
		{{-0.5f,-0.5f, -0.5f}, {1.0f, 1.0f}},
		// -X
		{{-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f}},
		{{-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f}},
		{{-0.5f,-0.5f,  0.5f}, {0.0f, 1.0f}},
		{{-0.5f,-0.5f, -0.5f}, {1.0f, 1.0f}},
		//  Z
		{{ 0.5f, 0.5f,  0.5f}, {0.0f, 0.0f}},
		{{-0.5f, 0.5f,  0.5f}, {1.0f, 0.0f}},
		{{ 0.5f,-0.5f,  0.5f}, {0.0f, 1.0f}},
		{{-0.5f,-0.5f,  0.5f}, {1.0f, 1.0f}},
	};
	int idx[] = {
		 0,  1,  2,  1,  3,  2,		// -Z
		 4,  5,  6,  5,  7,  6,		//  Y
		 8,  9, 10,  9, 11, 10,		//  X
		12, 13, 14, 13, 15, 14,		// -Y
		16, 17, 18, 17, 19, 18,		// -X
		20, 21, 22, 21, 23, 22,		//  Z
	};
	// バッファの作成
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = sizeof(vtx) / sizeof(Vertex);			// 頂点の数
	desc.vtxSize = sizeof(Vertex);							// 頂点一つあたりのデータサイズ
	desc.pIdx = idx;
	desc.idxCount = sizeof(idx) / sizeof(int);				// インデックスの数
	desc.idxSize = sizeof(int);								// インデックス一つあたりのデータサイズ
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;	// 直方体を表示するためのトポロジー

	m_pBox = new MeshBuffer();
	m_pBox->Create(desc);
}

void Geometory::MakeCylinder()
{
	//--- 頂点の作成
	// 天面、底面

	// 側面

	//--- インデックスの作成
	// 天面、底面

	// 側面


	//--- バッファの作成
}

void Geometory::MakeSphere()
{
	//--- 頂点の作成

	//--- インデックスの作成

	// バッファの作成
}