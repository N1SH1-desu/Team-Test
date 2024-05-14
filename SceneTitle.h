#pragma once
#include "Scene.h"
#include "GameLib/game_lib.h"

class SceneTitle : public Scene
{
private:
	void init() override;
	void update() override;
	void draw() override;
private:
	GameLib::Sprite* title = nullptr;
};
