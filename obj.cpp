#include <iostream>
#include <iomanip>
#include <cmath>

#include "obj.h"


void Obj::math(int t)
{
     position.x-= 5;

    if (accele == 0)t += 5;
    if (t > 10)
    {
        accele++;
        t = 0;
    }
    position.y += accele;
}

