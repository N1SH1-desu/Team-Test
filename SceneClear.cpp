#include "SceneClear.h"
#include "./GameLib/game_lib.h"
#include "WinMain.h"
#include "Audio.h"
#include <stdio.h>
#include<windows.h>
#include <time.h>
#include <sstream>
#include <iomanip>

using namespace std;
int v;

void SceneClear::init()
{
    timer = 0;
    cleartimer = 0;
    v = 0;
    GameLib::music::play(Audio::Music::CLEAR, true);
}

void SceneClear::update()
{
    if (timer > 60 * 5)
    {
        setScene(SCENE::TITLE);
    }
    if (timer > 0x40 && GameLib::input::TRG(0))
    {
        setScene(SCENE::TITLE);
    }

    timer++;
}

void SceneClear::draw()
{
    GameLib::clear(0, 0, 0);

    std::ostringstream oss1;

    oss1 << "SCORE:" << std::setw(8) << std::setfill('0') << v << "seconds";
    GameLib::font::textOut(4, oss1.str(), { 200,200 }, { 2,2 }, { 1,0,0,1 });
    if (v < 200)
    {
        v++;
        v++;

    }
}
void SceneClear::deinit()
{
    GameLib::music::stop(Audio::Music::CLEAR);
}