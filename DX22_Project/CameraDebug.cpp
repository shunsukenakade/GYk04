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
	if (IsKeyPress(VK_UP))		{ m_look.z += MOVE_SPEED; }
	if (IsKeyPress(VK_DOWN))	{ m_look.z -= MOVE_SPEED; }
	if (IsKeyPress(VK_LEFT))	{ m_look.x -= MOVE_SPEED; }
	if (IsKeyPress(VK_RIGHT))	{ m_look.x += MOVE_SPEED; }
	if (IsKeyPress(VK_SHIFT))	{ m_look.y += MOVE_SPEED; }
	if (IsKeyPress(VK_CONTROL)) { m_look.y -= MOVE_SPEED; }

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
	m_pos.x = cosf(m_radY) * cosf(m_radXZ) * m_radius + m_look.x;
	m_pos.y = sinf(m_radY) * m_radius + m_look.y;
	m_pos.z = cosf(m_radY) * sinf(m_radXZ) * m_radius + m_look.z;
	// カメラの上方向の計算
	m_up.x = cosf(m_radY + M_PI / 2) * cosf(m_radXZ);
	m_up.y = sinf(m_radY + M_PI / 2);
	m_up.z = cosf(m_radY + M_PI / 2) * sinf(m_radXZ);
}
