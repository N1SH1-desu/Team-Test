#pragma once
#include "GameLib/vector.h"
class Player
{
 public:
    VECTOR2 player_pos;
    float angle;

};
    void playerinit();
    void playerdeinit();
    void playerupdate();
    void playerrender();