#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

#include "Model.h"
#include "Camera.h"

class SceneGame
{
public:
	SceneGame();
	~SceneGame();
	void Update();
	void Draw();

private:
	Camera* _camera;
};

#endif // __SCENE_GAME_H__