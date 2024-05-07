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

void BreakObj::BreakMath(VECTOR2 pos)
{
    BreakPos = pos;
    BreakPos.y += 4;

    BreakPos.x;


    // 定数
    const double g = 9.81; // 重力加速度 (m/s^2)
    const double t_start = 0; // 開始時間 (s)
    const double t_end = 10; // 終了時間 (s)
    const double dt = 0.01; // 時間刻み (s)

    // 初期条件の設定
    const double y_start = pos.y; // 初期位置 (m)
    const double v_start = 0; // 初期速度 (m/s)

  
        // 時間の配列を作成
        double t = t_start;

        // 初期位置と速度の設定
        double y = y_start;
        double v = v_start;

        // 落下の計算
        //std::cout << "時間(s)\t位置(m)\t速度(m/s)\n";
        while (t <= t_end) {
            // 速度の更新
            v = v - g * dt;
            // 位置の更新
            y = y + v * dt;
            // 次の時間刻みへ
            t += dt;
        }
}

