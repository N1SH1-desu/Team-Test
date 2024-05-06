#pragma once
#include "CpuTimer.h"

class KeyManager
{
public:
    KeyManager();
    ~KeyManager();

    void Kye();

    const bool& GetKeyDown() const { return keydown; }

private:
    bool keydown = false;
    CpuTimer* timer;
};

