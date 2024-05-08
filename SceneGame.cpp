#include "SceneGame.h"
#include "./GameLib/game_lib.h"
#include "WinMain.h"


void SceneGame::init()
{
	p = new MusicData("music.txt");

	p->getNoteManager().InitNotes();
}

void SceneGame::update()
{
	if (!is)
	{
		timer.Start();
		key.KyeTimerStart();
		is = true;
	}

	timer.Tick();

	key.KyeUpdate();
	p->getNoteManager().UpdateNotes(timer.DeltaTime(), key.GetKeyDownTime());

	// シーン切り替えチェック
	if (GameLib::input::STATE(0) & GameLib::input::PAD_TRG1) { setScene(SCENE::OVER); }
	if (GameLib::input::STATE(0) & GameLib::input::PAD_TRG2) { setScene(SCENE::CLEAR); }
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
}

void SceneGame::uninit()
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}
