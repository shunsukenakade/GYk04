#pragma once
#include "GameObject.h"
class Goal : public GameObject
{
public:
	Goal();

	void Update() override;
	void CheckCollision(GameObject* other);
	void OnCollision();
};

