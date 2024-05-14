#include "Audio.h"
#include "GameLib/game_lib.h"

void Audio::loadAudio()
{
	loadMusic();
	setMusicVolume();
	loadSound();
	setSoundVolume();
}

void Audio::unloadAudio()
{
	GameLib::music::clear();
}

void Audio::loadMusic()
{
	//GameLib::music::load(Music::TITLE, AudioPaths::Music::TITLE);
	GameLib::music::load(Music::GAME, AudioPaths::Music::GAME);
	//GameLib::music::load(Music::CLEAR, AudioPaths::Music::CLEAR);

}

void Audio::setMusicVolume()
{
	//GameLib::music::setVolume(Music::WARNING, 1.0f);
}

void Audio::loadSound()
{
	//GameLib::sound::load(Sound::THROW, AudioPaths::Sound::THROW);
	GameLib::music::load(Music::SHOT, AudioPaths::Sound::SHOT);
}

void Audio::setSoundVolume()
{
	//GameLib::sound::setVolume(Sound::STAGE1, Stage1::SHOT, 1.0f);
}

