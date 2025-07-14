#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

#include "Model.h"
#include "Camera.h"

#include "Command.h"
#include "ActionBase.h"

class SceneGame
{
public:
	SceneGame();
	~SceneGame();
	void Update();
	void Draw();

private:
	Model* m_pModel;
	Camera* m_pCamera;
	Command* m_pCommand;
	std::vector<ActionBase> m_actionList;
};

#endif // __SCENE_GAME_H__