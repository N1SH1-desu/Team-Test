#pragma once
#include "GameLib/sprite.h"
#include "GameLib/game_lib.h"
#include <iostream>
#include <cmath>
#include <cstdlib> // system�֐����g�p���邽�߂ɕK�v
#include <random>
using namespace std;

class breakObj
{
public:
    VECTOR2 hahen_pos[8];
    GameLib::Sprite* hahen[4];
    int speedX;
    int speedY;
    int tt;
    int acceleG[8];
    int branch[8];
    int Rotate[8];
    int angle[8];
    int RotateSpeed[8];
    int maxa;
    float rate;

    void Break_init(float posx, float posy);
    void defoultg();
    void Break_update();
    void Break_render();
};
