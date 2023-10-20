#pragma comment(lib, "winmm.lib")
#pragma once
#include <Windows.h>
#include <string>


class Sound {
private:
	std::wstring alias;

	//Play and stop sound
	void repeatSound();
	void pauseSound();
	void resumeSound();
	void playSound();

	//Open and close file
	void openSound();
	void closeSound();

public:
	struct SoundSetting {
		bool backgroundSound = true;
		bool effectSound = true;
		bool backgroundPlaying = false;
		bool firstTimePlaying = true;
		int backgroundVolume = 100;
		int effectVolume = 100;
	};

	//Effect sound's path
	std::wstring path;
	const std::wstring CAR_CRASH = L"Sound\\CarCrash.wav";
	const std::wstring BACKGROUND = L"Sound\\BackgroundMusic.mp3";

	void playBackgroundSound(SoundSetting& soundSetting);
	void playEffectSound(SoundSetting soundSetting);

	//Set volume
	void turnUpVolume(SoundSetting& sound);
	void turnDownVolume(SoundSetting& sound);
};

