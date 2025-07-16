#include "Goal.h"
#include <time.h>

Goal::Goal()
{
    _model = new Model();
    if (!_model->Load("Assets/Models/sphere.fbx", 1.0f, Model::None)) {
        MessageBox(NULL, "Assets/Models/sphere.fbx", "Error", MB_OK);
    }

	_scale = { 3.0f, 3.0f, 3.0f };
	_position.x = rand() % 90 + 50.0f;
	_position.y = rand() % 100 - 50.0f;
}

void Goal::Update()
{
}

void Goal::CheckCollision(GameObject* other)
{
	float xDiff = _position.x - other->GetPosition().x;
	float yDiff = _position.y - other->GetPosition().y;
	float zDiff = _position.z - other->GetPosition().z; 
	float distance = sqrtf(xDiff * xDiff + yDiff * yDiff + zDiff * zDiff);

	if (distance < _scale.x + other->GetScale().x + 2.0f) {
		OnCollision();
	}
}

void Goal::OnCollision()
{
	_position.x = rand() % 90 + 50.0f;
	_position.y = rand() % 100 - 50.0f;
}