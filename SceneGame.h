#pragma once
#include "Scene.h"
#include "CpuTimer.h"
#include "MusicData.h"
#include "KeyManager.h"
#include "GameLib/sprite.h"

class SceneGame : public Scene
{
public:
	void uninit();
private:
	void init() override;
	void update() override;
	void draw() override;

private:
	bool is = false;
	CpuTimer timer;
	MusicData* p;
	KeyManager key;
	GameLib::Sprite* back_image;
	GameLib::Sprite* gun_left;
	GameLib::Sprite* gun_right;
};
