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

void KeyManager::KyeTimerStart()
{
	timer->Start();
}

void KeyManager::KyeUpdate()
{
	using namespace GameLib::input;
	if (TRG(0) & PAD_LEFT)
	{
		timer->Tick();
	}
	keydown_time = timer->DeltaTime();
	GameLib::debug::setString("keydownTime : %f", keydown_time);
}
