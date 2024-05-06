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
    using namespace GameLib::input;
    if (TRG(0) & PAD_LEFT && !keydown)
    {
        keydown = true;
        timer->Start();
    }
    timer->Tick();
    float delta = timer->DeltaTime();
    if (0.1f <= delta)
    {
        keydown = false;
    }
    GameLib::debug::setString("keydown : %d", keydown);
    GameLib::debug::setString("delta key : %f", delta);
}
