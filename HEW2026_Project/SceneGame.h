#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

#include "Scene.h"
#include "Model.h"
#include "Camera.h"
#include "player.h"
#include "Items.h"

class SceneGame : public Scene
{
public:
	SceneGame();
	~SceneGame();
	void Update() final;
	void Draw() final;


private:
	Player* m_player;
	Camera* m_pCamera;
	//Items* m_items;
	std::vector<Items*> m_items;  // multiple item objects
};

#endif // __SCENE_GAME_H__