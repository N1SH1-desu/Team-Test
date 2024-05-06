#include "KeyManager.h"
#include "./GameLib/game_lib.h"

KeyManager::KeyManager() :
    keydown(false),
    timer(nullptr)
{
    timer = new CpuTimer;
}

KeyManager::~KeyManager()
{
    delete timer;
    timer = nullptr;
}

void KeyManager::Kye()
{
    timer->Tick();
    using namespace GameLib::input;
    if (TRG(0) & PAD_LEFT && !keydown)
    {
        keydown = true;
        timer->Start();
    }
    float delta = timer->DeltaTime();
    if (0.1f <= delta)
    {
        keydown = false;
        timer->Start();
    }

    GameLib::debug::setString("keydown : %d", keydown);
    GameLib::debug::setString("delta key : %f", delta);
}
