#include "BreakObj.h"

void breakObj::defoultg()
{

    maxa = 8;
    tt = 0;
    std::random_device rnd;     // 非決定的な乱数生成器を生成
    std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
    std::uniform_int_distribution<> rand10(0, 9);        // [0, 99] 範囲の一様乱数
    for (int i = 0; i < maxa; ++i) {
        acceleG[i] = -rand10(mt);

    }
    std::uniform_int_distribution<> rand11(3, 12);
    for (int i = 0; i < maxa; ++i)
    {
        RotateSpeed[i] = rand11(mt);
    }
    std::uniform_int_distribution<> rand100(0, 100);
    for (int i = 0; i < maxa; ++i) {
        branch[i] = rand100(mt);

    }

    std::uniform_int_distribution<> rand1000(0, 1000);
    for (int i = 0; i < maxa; ++i) {
        Rotate[i] = rand1000(mt);
        Rotate[i] %= 2;
        if (Rotate[i] == 0)Rotate[i] = -1;
    }


    tt = 0;


}


void breakObj::Break_init(float posx, float posy)
{
    hahen[0] = GameLib::sprite_load(L"Data/Images/hahen1.png");
    hahen[1] = GameLib::sprite_load(L"Data/Images/hahen2.png");
    hahen[2] = GameLib::sprite_load(L"Data/Images/hahen3.png");
    hahen[3] = GameLib::sprite_load(L"Data/Images/ginn.png");


    speedX = 6;
    speedY = 6;

    defoultg();

    for (int i = 0; i < maxa; ++i)
    {
        branch[i] %= 2;
        if (branch[i] == 0)branch[i] = -1;
        hahen_pos[i] = { posx,posy };
    }

}

void breakObj::Break_update()
{
    for (int i = 0; i < maxa; ++i)
    {
        hahen_pos[i].y += speedY;
        hahen_pos[i].x = hahen_pos[i].x + (branch[i] * -1) * 5;
    }



    
    if (acceleG == 0)tt += 5;
    if (tt > 10)
    {
        for (int i = 0; i < maxa; ++i)
        {
            acceleG[i]++;

        }

        tt = 0;
    }

    for (int i = 0; i < maxa; ++i)
    {
        hahen_pos[i].y += acceleG[i];
        angle[i] = angle[i] + (RotateSpeed[i] * Rotate[i]);
    }


    tt++;
}

void breakObj::Break_render()
{
    GameLib::sprite_render(hahen[0], hahen_pos[0].x, hahen_pos[0].y, 0.35f, 0.35f, 1, 1, 512, 512, 512 / 2, 512 / 2, DirectX::XMConvertToRadians(angle[0]));
    GameLib::sprite_render(hahen[1], hahen_pos[1].x, hahen_pos[1].y, 0.35f, 0.35f, 1, 1, 512, 512, 512 / 2, 512 / 2, DirectX::XMConvertToRadians(angle[1]));
    GameLib::sprite_render(hahen[2], hahen_pos[2].x, hahen_pos[2].y, 0.35f, 0.35f, 1, 1, 512, 512, 512 / 2, 512 / 2, DirectX::XMConvertToRadians(angle[2]));
    GameLib::sprite_render(hahen[3], hahen_pos[3].x, hahen_pos[3].y, 0.35f, 0.35f, 1, 1, 512, 512, 512 / 2, 512 / 2, DirectX::XMConvertToRadians(angle[3]));
    GameLib::sprite_render(hahen[0], hahen_pos[4].x, hahen_pos[4].y, 0.35f, 0.35f, 1, 1, 512, 512, 512 / 2, 512 / 2, DirectX::XMConvertToRadians(angle[4]));
    GameLib::sprite_render(hahen[1], hahen_pos[5].x, hahen_pos[5].y, 0.35f, 0.35f, 1, 1, 512, 512, 512 / 2, 512 / 2, DirectX::XMConvertToRadians(angle[5]));
    GameLib::sprite_render(hahen[2], hahen_pos[6].x, hahen_pos[6].y, 0.35f, 0.35f, 1, 1, 512, 512, 512 / 2, 512 / 2, DirectX::XMConvertToRadians(angle[6]));
    GameLib::sprite_render(hahen[3], hahen_pos[7].x, hahen_pos[7].y, 0.35f, 0.35f, 1, 1, 512, 512, 512 / 2, 512 / 2, DirectX::XMConvertToRadians(angle[7]));
}
