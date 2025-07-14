#include "Spring.h"
#include <WinUser.h>

Spring::Spring()
{
    _model = new Model();
    if (!_model->Load("Assets/Models/sphere.fbx", 1.0f, Model::None)) {
        MessageBox(NULL, "Assets/Models/sphere.fbx", "Error", MB_OK);
    }
}

void Spring::Update()
{
	// マウスの位置を取得
	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(GetActiveWindow(), &mousePos); // ウィンドウのクライアント座標に変換

	// 例えばオフセットが必要なら調整
	float mx = static_cast<float>(mousePos.x - 640);
	float my = static_cast<float>(mousePos.y - 360);

	// 一番上のノードの位置をマウスに合わせる
	_position.x = mx;
	_position.y = my;
}
