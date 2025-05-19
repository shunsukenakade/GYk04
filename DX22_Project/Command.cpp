#include "Command.h"
#include "Defines.h"
#include <iostream>
#include "ActionBase.h"

#define MAX_STACK (60)
#define TOLERANCE (10)	// コマンドとコマンドの間の猶予

// デフォルトのキーコンフィグ
#define DEFAULT_KEY_UP		(VK_SPACE)
#define DEFAULT_KEY_DOWN	('S')
#define DEFAULT_KEY_LEFT	('A')
#define DEFAULT_KEY_RIGHT	('D')
#define DEFAULT_KEY_LP		('U')
#define DEFAULT_KEY_MP		('I')
#define DEFAULT_KEY_HP		('O')
#define DEFAULT_KEY_LK		('J')
#define DEFAULT_KEY_MK		('K')
#define DEFAULT_KEY_HK		('L')

Command::Command()
	:m_keyConfig{
		DEFAULT_KEY_UP, DEFAULT_KEY_DOWN, DEFAULT_KEY_LEFT, DEFAULT_KEY_RIGHT,
		DEFAULT_KEY_LP, DEFAULT_KEY_MP, DEFAULT_KEY_HP,
		DEFAULT_KEY_LK, DEFAULT_KEY_MK, DEFAULT_KEY_HK
	}
	, m_pArrowTex(nullptr)
{
	m_pArrowTex = new Texture();
	if (FAILED(m_pArrowTex->Create("Texture/arrow.jpg"))) {
		MessageBox(NULL, "Texture load failed.¥nUI.cpp", "Error", MB_OK);
	}

}

Command::~Command()
{
	if (m_pArrowTex) {
		delete m_pArrowTex;
		m_pArrowTex = nullptr;
	}
}

void Command::Update()
{
	//=============== 現在の入力状況を構造体に格納 ===============

	COMMAND nowInput;

	// 方向入力をテンキー表記に変換
	int direction = 5;	// ニュートラル状態
	if (IsKeyPress(m_keyConfig.UP)) { direction += 3; }
	if (IsKeyPress(m_keyConfig.DOWN)) { direction -= 3; }
	if (IsKeyPress(m_keyConfig.LEFT)) { direction -= 1; }
	if (IsKeyPress(m_keyConfig.RIGHT)) { direction += 1; }
	nowInput.direction = direction;

	nowInput.LP = IsKeyPress(m_keyConfig.LP);
	nowInput.MP = IsKeyPress(m_keyConfig.MP);
	nowInput.HP = IsKeyPress(m_keyConfig.HP);
	nowInput.LK = IsKeyPress(m_keyConfig.LK);
	nowInput.MK = IsKeyPress(m_keyConfig.MK);
	nowInput.HK = IsKeyPress(m_keyConfig.HK);

	//=============== 現在の入力からコマンドが成立しているかチェック ===============

	for (auto action : m_actionList)
	{
		bool endFlag = false;

		std::vector<COMMAND> command = action->GetCommand();	// 技のコマンドを取得
		std::vector<COMMAND>::reverse_iterator comItr = command.rbegin();		// コマンドのリバースイテレータ

		std::list<INPUT_DATA>::reverse_iterator logItr = m_inputLog.rbegin();	// 入力ログのリバースイテレータ
		int frame = 0;

		if (!nowInput.Check(*comItr)) { continue; }	// 現在の入力が技の最後のコマンドを満たしているか
		comItr++;

		for (; comItr != command.rend(); comItr++)	// 以降のコマンドを逆順に判定
		{
			if (endFlag)
			{
				break;
			}
			for (; (logItr != m_inputLog.rend()); logItr++)	// 入力ログから探索
			{
				if (frame >= TOLERANCE) // 猶予フレーム
				{
					endFlag = true;
					break;
				}

				if ((*logItr).command.Check(*comItr))
				{
					frame = (*logItr).frame;
					break;
				}
				else
				{
					frame += (*logItr).frame;
				}
			}
		}
		if (!endFlag)	// endFlagで終了していなかった場合→判定を完走し、コマンドが成立
			action->Action();
	}

	//=============== 作成した構造体をスタック(list)に格納 ===============

	// 同じ入力が継続されているか
	if (!m_inputLog.empty() && nowInput == m_inputLog.back().command) {
		m_inputLog.back().frame++;		// 入力フレーム加算
	}
	else {
		m_inputLog.push_back({ nowInput, 1 });	// 現在の情報をプッシュ
	}

	if (m_inputLog.size() > MAX_STACK)
		m_inputLog.pop_front();	// 過去の情報をポップ


}

void Command::Draw()
{
	//=============== デバッグ用コンソール表示 ===============
	//std::system("cls");

	std::string temp;
	temp += m_inputLog.back().command.LP ? "LP" : "  ";
	temp += m_inputLog.back().command.MP ? "MP" : "  ";
	temp += m_inputLog.back().command.HP ? "HP" : "  ";
	temp += m_inputLog.back().command.LK ? "LK" : "  ";
	temp += m_inputLog.back().command.MK ? "MK" : "  ";
	temp += m_inputLog.back().command.HK ? "HK" : "  ";
	// 前フレームと違う入力なら改行　同じなら最新の行を上書き
	if ((!m_inputLog.empty() && m_inputLog.back().frame > 1))
		std::cout << "\r";
	else
		std::cout << "\n";
	std::cout << m_inputLog.back().command.direction << ' ' << temp << ":" << m_inputLog.back().frame;
	

	//// スプライトの表示に必要な行列を計算
	//DirectX::XMFLOAT4X4 world, view, proj;
	//DirectX::XMMATRIX mView =
	//	DirectX::XMMatrixLookAtLH(
	//		{ 0.0f, 0.0f, -10.0f },
	//		{ 0.0f, 0.0f, 0.0f },
	//		{ 0.0f, 1.0f, 0.0f });
	//DirectX::XMMATRIX mProj = DirectX::XMMatrixOrthographicOffCenterLH(
	//	0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.01f, 1000.0f);
	//mView = DirectX::XMMatrixTranspose(mView);
	//DirectX::XMStoreFloat4x4(&view, mView);
	//mProj = DirectX::XMMatrixTranspose(mProj);
	//DirectX::XMStoreFloat4x4(&proj, mProj);
	//Sprite::SetView(view);
	//Sprite::SetProjection(proj);

	//// 方向キー表示
	//if (m_comNow.direction != 5) // ニュートラルのときは表示しない
	//{
	//	DirectX::XMFLOAT2 pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	//	DirectX::XMFLOAT2 size = { 50.0f, 50.0f };
	//	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(pos.x - size.x * 0.5f, pos.y - size.y * 0.5f, 0.0f);
	//	DirectX::XMMATRIX radius = DirectX::XMMatrixTranslation(50.0f, 0.0f, 0.0f);
	//	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);
	//	DirectX::XMMATRIX R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(0.0f));
	//	switch (m_comNow.direction)
	//	{
	//	case 6: R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(0.0f)); break;
	//	case 3: R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(45.0f)); break;
	//	case 2: R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(90.0f)); break;
	//	case 1: R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(135.0f)); break;
	//	case 4: R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(180.0f)); break;
	//	case 7: R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(225.0f)); break;
	//	case 8: R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(270.0f)); break;
	//	case 9: R = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(315.0f)); break;
	//	}
	//	DirectX::XMMATRIX mWorld = S * radius * R * T;	// 回転行列の前に移動行列radiusをかける
	//	mWorld = DirectX::XMMatrixTranspose(mWorld);
	//	DirectX::XMStoreFloat4x4(&world, mWorld);
	//	Sprite::SetWorld(world); // スプライトのワールド行列を設定
	//	Sprite::SetSize(size); // スプライトのサイズを設定
	//	Sprite::SetOffset({ size.x * 0.5f, 0.0f }); // スプライトの原点を変更
	//	Sprite::SetTexture(m_pArrowTex); // テクスチャを設定
	//	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	//	Sprite::Draw();
	//}


}
