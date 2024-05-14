#pragma once
namespace AudioPaths
{

	namespace Music
	{
		//inline const wchar_t* TITLE;
		inline const wchar_t* GAME = L"./Data/Musics/Western.wav";
		//inline const wchar_t* CLEAR;
	}

	namespace Sound
	{
		//inline const wchar_t* THROW = L"Data/Musics/throw.wav";
		inline const wchar_t* SHOT = L"Data/Musics/shot_sound.wav";
		//inline const wchar_t* CASK;

	}

}

class Audio
{
public:
	enum Music
	{
		GAME,
		SHOT,
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