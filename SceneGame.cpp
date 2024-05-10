#include "SceneGame.h"
#include "./GameLib/game_lib.h"
#include "WinMain.h"
#include "audio.h"
#include "BreakObj.h"

int game_timer;

breakObj taru;
breakObj bin;
breakObj hako;
GameLib::Sprite* haikei;

GameLib::Sprite* Right;
GameLib::Sprite* Left;

void SceneGame::init()
{
	p = new MusicData("music.txt");

	p->getNoteManager().InitNotes();

	Right = GameLib::sprite_load(L"Data/Images/juu_migi.png");
	Left = GameLib::sprite_load(L"Data/Images/juu_hidari.png");

	haikei = GameLib::sprite_load(L"Data/Images/game.png");

	taru.hahen[0] = GameLib::sprite_load(L"Data/Images/hahen1.png");
	taru.hahen[1] = GameLib::sprite_load(L"Data/Images/hahen2.png");
	taru.hahen[2] = GameLib::sprite_load(L"Data/Images/hahen3.png");
	taru.hahen[3] = GameLib::sprite_load(L"Data/Images/ginn.png");

	bin.hahen[0] = GameLib::sprite_load(L"Data/Images/bin1.png");
	bin.hahen[1] = GameLib::sprite_load(L"Data/Images/bin4.png");
	bin.hahen[2] = GameLib::sprite_load(L"Data/Images/bin3.png");
	bin.hahen[3] = GameLib::sprite_load(L"Data/Images/bin5.png");

	bin.hahen[0] = GameLib::sprite_load(L"Data/Images/hako1.png");
	bin.hahen[1] = GameLib::sprite_load(L"Data/Images/hako2.png");
	bin.hahen[2] = GameLib::sprite_load(L"Data/Images/hako3.png");
	bin.hahen[3] = GameLib::sprite_load(L"Data/Images/hako4.png");


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

	
	timer.Tick();

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

	GameLib::sprite_render(haikei, 1, 1);
	p->getNoteManager().DrawNotes();

	// 文字列描画
	/*GameLib::font::textOut(4, "[Z]GAME OVER", { 0, 660 }, { 2, 2 },
		{ 1, 0, 0, 1 }, GameLib::TEXT_ALIGN::MIDDLE_LEFT);

	GameLib::font::textOut(4, "[X]GAME CLEAR", { 0, 700 }, { 2, 2 },
		{ 0, 1, 1, 1 }, GameLib::TEXT_ALIGN::MIDDLE_LEFT);*/
	GameLib::sprite_render(Right, 900, 600, 0.6f, 0.6f);
	GameLib::sprite_render(Left, 100, 600, 0.6f, 0.6f);

}

void SceneGame::uninit()
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}
void SceneGame::deinit()
{
	//GameLib::music::stop(Audio::Music::GAME);

}
