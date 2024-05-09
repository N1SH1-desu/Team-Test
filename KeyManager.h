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
	const float& GetKeyDownTimeLeft() const { return keydown_time_left; }
	const float& GetKeyDownTimeRight() const { return keydown_time_right; }

private:
	bool keydown = false;
	CpuTimer* timer = nullptr;
	float keydown_time_left = 0.0f;
	float keydown_time_right = 0.0f;
};

