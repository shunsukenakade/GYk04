#pragma once
#include "GameObject.h"
#define BALL_MASS 3.0f

class Ball : public GameObject
{
public:
	Ball();
	void Update() override;

	void SetVelocity(DirectX::XMVECTOR velocity) { _velocity = velocity; }

	void SetAttached(bool isAttached) { _isAttached = isAttached; }
	bool GetAttached() { return _isAttached; }

private:

	DirectX::XMVECTOR _velocity = { 0.0f, 0.0f, 0.0f };
	bool _isAttached = true;	// ÇŒÇÀÇ…ê⁄ë±Ç≥ÇÍÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©
};

