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
		keydown_time_left = timer->DeltaTime();
	}
	if (TRG(0) & PAD_RIGHT)
	{
		timer->Tick();
		keydown_time_right = timer->DeltaTime();
	}
	GameLib::debug::setString("keydownTimeLeft : %f", keydown_time_left);
	GameLib::debug::setString("keydownTimeRight : %f", keydown_time_right);
}
