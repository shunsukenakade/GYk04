#include "CameraDebug.h"
#define SPEED (0.1)
#define MOVE_SPEED (0.5)
#define _USE_MATH_DEFINES
#include "math.h"

#define KEY_UP		('W')
#define KEY_LEFT	('A')
#define KEY_DOWN	('S')
#define KEY_RIGHT	('D')
#define KEY_FRONT	('E')
#define KEY_BACK	('Q')

CameraDebug::CameraDebug()
	: m_radXZ(M_PI / 2 * 3)
	, m_radY(0.0f)
	, m_radius(10.0f)
{
}

CameraDebug::~CameraDebug()
{
}

void CameraDebug::Update()
{
	// 注視点の移動
	if (IsKeyPress(VK_UP))		{ _look.z += MOVE_SPEED; }
	if (IsKeyPress(VK_DOWN))	{ _look.z -= MOVE_SPEED; }
	if (IsKeyPress(VK_LEFT))	{ _look.x -= MOVE_SPEED; }
	if (IsKeyPress(VK_RIGHT))	{ _look.x += MOVE_SPEED; }
	if (IsKeyPress(VK_SHIFT))	{ _look.y += MOVE_SPEED; }
	if (IsKeyPress(VK_CONTROL)) { _look.y -= MOVE_SPEED; }

	// ---カメラ位置の移動
	// 回り込みの処理
	if (IsKeyPress(KEY_UP)) { m_radY -= SPEED; }
	if (IsKeyPress(KEY_RIGHT)) { m_radXZ -= SPEED; }
	if (IsKeyPress(KEY_DOWN)) { m_radY += SPEED; }
	if (IsKeyPress(KEY_LEFT)) { m_radXZ += SPEED; }
	// カメラの距離を変える処理
	if (IsKeyPress(KEY_BACK)) { m_radius += SPEED; }
	if (IsKeyPress(KEY_FRONT)) { m_radius -= SPEED; }

	// カメラの位置の計算
	_pos.x = cosf(m_radY) * cosf(m_radXZ) * m_radius + _look.x;
	_pos.y = sinf(m_radY) * m_radius + _look.y;
	_pos.z = cosf(m_radY) * sinf(m_radXZ) * m_radius + _look.z;
	// カメラの上方向の計算
	_up.x = cosf(m_radY + M_PI / 2) * cosf(m_radXZ);
	_up.y = sinf(m_radY + M_PI / 2);
	_up.z = cosf(m_radY + M_PI / 2) * sinf(m_radXZ);
}
