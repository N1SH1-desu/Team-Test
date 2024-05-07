#include "player.h"
#include "GameLib/game_lib.h"
#include "GameLib/sprite.h"
#include "Audio.h"
GameLib::Sprite* SprPlayer;
Player Right;
Player Left;
void playerinit()
{
    Audio::loadAudio();
    Right.player_pos.x = 700;
    Right.player_pos.y = 1000;
    Left.player_pos.x = 200;
    Left.player_pos.y = 1000;
    
    //SprPlayer=GameLib::sprite_load(L"Data/Images/" );

}


void playerupdate()
{
    if (GameLib::input::STATE(0) & GameLib::input::PAD_START)
    {
        
        GameLib::music::play(Audio::Sound::SHOT,false);
    }

    if (GameLib::input::STATE(0) & GameLib::input::PAD_L2)
    {
        GameLib::music::play(Audio::Sound::SHOT,false);
    }

}

void playerrender()
{

}

void playerdeinit()
{

}