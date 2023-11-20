#pragma comment(lib, "winmm.lib")
#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <mmsystem.h>
#include <iostream>


class Sound {
public: 
	struct SoundSetting {
		bool backgroundSound = true;
		bool effectSound = true;
		bool backgroundPlaying = false;
		bool firstTimePlaying = true;
		int backgroundVolume = 100;
		int effectVolume = 100;
	};
private:
	//Play and stop sound
	static void repeatSound(std::wstring alias);
	static void playSound(std::wstring alias);
	static void pauseSound(std::wstring alias);
	static void resumeSound(std::wstring alias);
	static void setAudio(std::wstring alias, int volume);

	//Open and close file
	static void openSound(std::wstring path);
	static void closeSound(std::wstring alias);

	static std::wstring findAlias(std::wstring path);

	static const std::vector <std::wstring> EFFECT;
	static const std::vector <std::wstring> BACKGROUND;

	Sound() {};

public: 
	//Path
	static enum class Background : char {
		BACKGROUND_MUSIC
	};
	static enum class Effect : char {
		CAR_CRASH,
		INVALID,
		VALID,
		ENTER,
		CHANGE
	};
	static void playBackgroundSound(Sound::SoundSetting& soundSetting, int preIndexSound, int indexSound);
	static void playEffectSound(Sound::SoundSetting& soundSetting, int indexSound);

	static void turnOffBackgroundSound(Sound::SoundSetting& soundSetting,int indexSound);
	static void turnOnBackgroundSound(Sound::SoundSetting& soundSetting,int indexSound);
	static void turnOffEffectSound(Sound::SoundSetting& soundSetting);
	static void turnOnEffectSound(Sound::SoundSetting& soundSetting);

	static bool turnUpBackgroundVolume(Sound::SoundSetting& soundSetting);
	static bool turnDownBackgroundVolume(Sound::SoundSetting& soundSetting);
	static bool turnUpEffectVolume(Sound::SoundSetting& soundSetting);
	static bool turnDownEffectVolume(Sound::SoundSetting& soundSetting);
};