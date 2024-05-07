#pragma once
#include "Scene.h"
#include "CpuTimer.h"
#include "MusicData.h"

class SceneGame : public Scene
{
public:
    void uninit();
private:
    void init() override;
    void deinit()override;
    void update() override;
    void draw() override;
    
private:
    bool is = false;
    int t;
    CpuTimer timer;
    MusicData* p;
};
