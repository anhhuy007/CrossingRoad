#include "Sound.h"
#include <Windows.h>
#include <string.h>
#include <iostream>
#include <string>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

//Open and close file
void Sound::openSound() {
	std::wstring open = L"open \"" + path + L"\" type mpegvideo alias " + alias;
	mciSendString(open.c_str(), NULL, 0, NULL);
}
void Sound::closeSound() {
	std::wstring close = L"close " + alias;
	mciSendString(close.c_str(), NULL, 0, NULL);
}

void Sound::playBackgroundSound(SoundSetting& soundSetting) {
	path = BACKGROUND;
	alias = L"BackgroundMusic";
	if (soundSetting.backgroundSound) {
		if (soundSetting.firstTimePlaying) {
			openSound();
			repeatSound();
			soundSetting.backgroundPlaying = true;
			soundSetting.firstTimePlaying = false;
		}
		else {
			resumeSound();
			soundSetting.backgroundPlaying = true;
		}
	}
	else {
		pauseSound();
		soundSetting.backgroundPlaying = false;
	}
}

void Sound::playEffectSound(SoundSetting soundSetting) {
	if (soundSetting.effectSound) {
		std::wstring play = L"play " + path;
		mciSendString(play.c_str(), NULL, 0, NULL);
	}
}

//Play and stop sound
void Sound::repeatSound() {
	std::wstring repeat = L"play " + alias + L" repeat";
	mciSendString(repeat.c_str(), NULL, 0, NULL);
}
void Sound::pauseSound() {
	std::wstring pause = L"pause " + alias;
	mciSendString(pause.c_str(), NULL, 0, NULL);
}
void Sound::resumeSound() {
	std::wstring resume = L"resume " + alias;
	mciSendString(resume.c_str(), NULL, 0, NULL);
}
void Sound::playSound() {
	std::wstring play = L"play " + alias;
	mciSendString(play.c_str(), NULL, 0, NULL);
}

//Adjust volume
void Sound::turnUpVolume(SoundSetting& sound) {
	int* volume;
	if (path == BACKGROUND)
		volume = &(sound.backgroundVolume);
	else
		volume = &(sound.effectVolume);
	if (*volume >= 100)
		*volume = 100;
	else
		*volume += 10;
	std::wstring turnUpVolume = L"setaudio " + alias + L" volume to " + std::to_wstring(*volume);
	mciSendString(turnUpVolume.c_str(), NULL, 0, NULL);
}
void Sound::turnDownVolume(SoundSetting& sound) {
	int* volume;
	if (path == BACKGROUND)
		volume = &(sound.backgroundVolume);
	else
		volume = &(sound.effectVolume);
	if (*volume <= 0)
		*volume = 0;
	else
		*volume -= 10;
	std::wstring turnDownVolume = L"setaudio " + alias + L" volume to " + std::to_wstring(*volume);
	mciSendString(turnDownVolume.c_str(), NULL, 0, NULL);
}

