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


    // �萔
    const double g = 9.81; // �d�͉����x (m/s^2)
    const double t_start = 0; // �J�n���� (s)
    const double t_end = 10; // �I������ (s)
    const double dt = 0.01; // ���ԍ��� (s)

    // ���������̐ݒ�
    const double y_start = pos.y; // �����ʒu (m)
    const double v_start = 0; // �������x (m/s)

  
        // ���Ԃ̔z����쐬
        double t = t_start;

        // �����ʒu�Ƒ��x�̐ݒ�
        double y = y_start;
        double v = v_start;

        // �����̌v�Z
        //std::cout << "����(s)\t�ʒu(m)\t���x(m/s)\n";
        while (t <= t_end) {
            // ���x�̍X�V
            v = v - g * dt;
            // �ʒu�̍X�V
            y = y + v * dt;
            // ���̎��ԍ��݂�
            t += dt;
        }
}

