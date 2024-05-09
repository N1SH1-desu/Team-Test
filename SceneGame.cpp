#include "SceneGame.h"
#include "./GameLib/game_lib.h"
#include "WinMain.h"


void SceneGame::init()
{
	p = new MusicData("music.txt");

	p->getNoteManager().InitNotes();

	timer.Start();
}

void SceneGame::update()
{
	static float before_music = 0.0f;
	timer.Tick();
	if (!is)
	{
		before_music = timer.DeltaTime();
		if (before_music >= 2.0f)
		{
			is = true;
			timer.ReStart();
			key.KyeTimerStart();
		}
	}

	if (is)
	{
		key.KyeUpdate();
		p->getNoteManager().UpdateNotes(timer.DeltaTime(), key.GetKeyDownTimeLeft(), key.GetKeyDownTimeRight());
	}

	if (timer.DeltaTime() >= 135)
	{
		setScene(SCENE::CLEAR);
	}
}

void SceneGame::draw()
{
	// 画面をクリア
	GameLib::clear(0, 0, 0);

	p->getNoteManager().DrawNotes();
}

void SceneGame::uninit()
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}
