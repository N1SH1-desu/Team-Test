#include "SceneGame.h"
#include "./GameLib/game_lib.h"
#include "WinMain.h"

int game_timer;
breakObj taru;
breakObj bin;
breakObj hako;

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
}

void SceneGame::uninit()
{
	if (p)
	{
		delete p;
		p = nullptr;
	}


}
