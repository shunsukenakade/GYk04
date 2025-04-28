#pragma once
#include "Camera.h"
#include "Input.h"
class CameraDebug : public Camera {
public:
	CameraDebug();
	~CameraDebug();
	void Update();

private:
	float m_radXZ;	// ƒJƒƒ‰‚Ì‰¡‰ñ“]
	float m_radY;	// ƒJƒƒ‰‚Ìc‰ñ“]
	float m_radius;	// ƒJƒƒ‰‚Æ’‹“_‚Ì‹——£
};