#include "SceneGame.h"
#include "./GameLib/game_lib.h"
#include "WinMain.h"
#include "Audio.h"

int game_timer;
breakObj taru;
breakObj bin;
breakObj hako;

void SceneGame::init()
{
	p = new MusicData("music.txt");

	p->getNoteManager().InitNotes();
	timer.Start();

	back_image = GameLib::sprite_load(L"./Data/Images/berte.png");
	gun_left = GameLib::sprite_load(L"./Data/Images/juu_hidari.png");
	gun_right = GameLib::sprite_load(L"./Data/Images/juu_migi.png");

	Audio::loadAudio();
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
			GameLib::music::play(Audio::Music::GAME, false);
		}
	}

	if (is)
	{
		key.KyeUpdate();
		p->getNoteManager().UpdateNotes(timer.DeltaTime(), key.GetKeyDownTimeLeft(), key.GetKeyDownTimeRight());
	}
	game_timer++;
}

void SceneGame::draw()
{
	// 画面をクリア
	GameLib::clear(0, 0, 0);

	GameLib::sprite_render(back_image, 0, 0, 1, 1, 0, 0, 1280, 720);
	GameLib::sprite_render(gun_left, 0, 720, 1, 1, 0, 0, 512, 512, 256, 256);
	GameLib::sprite_render(gun_right, 1280, 720, 1, 1, 0, 0, 512, 512, 256, 256);

	p->getNoteManager().DrawNotes();

}

void SceneGame::uninit()
{
	if (p)
	{
		delete p;
		p = nullptr;
	}

	Audio::unloadAudio();
}
