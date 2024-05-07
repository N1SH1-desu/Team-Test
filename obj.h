#pragma once
#include"SceneGame.h";
#include "GameLib/vector.h";
class Obj 
{
public:
    VECTOR2 position;
    int accele;//‰Á‘¬“x
    int angle;
    float scale;
    bool isbreak;
public:
    void math(int t);
};

class BreakObj
{
private:
    VECTOR2 BreakPos;
    int Breaktimer;
    float BreakScale;
public:
    void BreakMath(VECTOR2 pos);
    
};
