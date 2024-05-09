#include "SceneGame.h"
#include "./GameLib/game_lib.h"
#include "WinMain.h"
#include <stdio.h>
#include <math.h>
#include "audio.h"


GameLib::Sprite* a[2];
int game_timer;
GameLib::Sprite* Right;
GameLib::Sprite* Left;

void SceneGame::init()
{
	p = new MusicData("music.txt");

	p->getNoteManager().InitNotes();

	Right = GameLib::sprite_load(L"Data/Images/juu_migi.png");
	Left = GameLib::sprite_load(L"Data/Images/juu_hidari.png");

}

void SceneGame::update()
{
	if (!is)
	{
		timer.Start();
		is = true;
	}
	timer.Tick();

	GameLib::debug::setString("currentTime: %lf", timer.DeltaTime());
	GameLib::debug::setString("option: %s", p->getOptionStream().str().c_str());
	GameLib::debug::setString("data: %s", p->getDataStream().str().c_str());

	GameLib::debug::setString("Title : %s", p->getOptions().song_name.c_str());
	GameLib::debug::setString("Wave : %s", p->getOptions().song_path.c_str());
	GameLib::debug::setString("BPM : %d", p->getOptions().bpm);
	GameLib::debug::setString("OFFSET : %f", p->getOptions().offset);
	GameLib::debug::setString("START : %d", p->getOptions().isStart);

	GameLib::debug::setString("note[0][0] : %lf", p->getNoteManager().getNoteTiming(0, 2));
	GameLib::debug::setString("note[0] size : %d", p->getNoteManager().getNoteTiming(0, 2));

	p->getNoteManager().UpdateNotes(timer.DeltaTime());

	// シーン切り替えチェック
	if (GameLib::input::STATE(0) & GameLib::input::PAD_TRG1) { setScene(SCENE::OVER); }
	if (GameLib::input::STATE(0) & GameLib::input::PAD_TRG2) { setScene(SCENE::CLEAR); }


	game_timer++;
}

void SceneGame::draw()
{
	// 画面をクリア
	GameLib::clear(0, 0, 0);

	p->getNoteManager().DrawNotes();

	// 文字列描画
	GameLib::font::textOut(4, "[Z]GAME OVER", { 0, 660 }, { 2, 2 },
		{ 1, 0, 0, 1 }, GameLib::TEXT_ALIGN::MIDDLE_LEFT);

	GameLib::font::textOut(4, "[X]GAME CLEAR", { 0, 700 }, { 2, 2 },
		{ 0, 1, 1, 1 }, GameLib::TEXT_ALIGN::MIDDLE_LEFT);
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
