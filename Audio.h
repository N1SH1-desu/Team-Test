#pragma once
namespace AudioPaths
{

	namespace Music
	{
		/*inline const wchar_t* TITLE;
		inline const wchar_t* GAME;
		inline const wchar_t* CLEAR;*/
	}

	namespace Sound
	{
		//inline const wchar_t* THROW;
		inline const wchar_t* SHOT = L"Data/Musics/shot_sound.wav";
		//inline const wchar_t* CASK;

	}

}

class Audio
{
public:
	enum Music
	{
		TITLE,
		GAME,
		CLEAR
	};

	enum Sound
	{
		THROW,
		SHOT,
		GLASS,
		BOX,
		CASK,
	};

	Audio() = default;
	~Audio() = default;

	static void loadAudio();
	static void unloadAudio();

private:
	static void loadMusic();
	static void setMusicVolume();
	static void loadSound();
	static void setSoundVolume();
};