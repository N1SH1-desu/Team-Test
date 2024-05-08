#pragma once
#include "CpuTimer.h"

class KeyManager
{
public:
	KeyManager();
	~KeyManager();

	void KyeTimerStart();
	void KyeUpdate();

	const bool& GetKeyDown() const { return keydown; }
	const float& GetKeyDownTime() const { return keydown_time; }

private:
	bool keydown = false;
	CpuTimer* timer = nullptr;
	float keydown_time = 0.0f;
};

