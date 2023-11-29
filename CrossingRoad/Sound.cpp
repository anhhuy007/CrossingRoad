#include "Sound.h"
#include <Windows.h>
#include <string.h>
#include <iostream>
#include <string>
#include <mmsystem.h>
#include <mutex>
#pragma comment(lib, "winmm.lib")

Sound* Sound::instance_ = nullptr;
std::mutex Sound::locker;

//--------------Path and alias of sound--------------
const std::vector<std::wstring> Sound::EFFECT = {
	L"Sound\\CarCrash.wav",
	L"Sound\\Invalid.wav",
	L"Sound\\Valid.mp3",
	L"Sound\\Enter.wav",
	L"Sound\\Change.mp3",
	L"Sound\\Coin.wav"
};
const std::vector<std::wstring> Sound::BACKGROUND = {
	L"Sound\\BackgroundMusic.mp3",
	L"Sound\\HighwayBackground.mp3"
};
std::wstring Sound::findAlias(std::wstring path) {
	if (path == L"Sound\\BackgroundMusic.mp3")
		return L"0";
	else if (path == L"Sound\\CarCrash.wav")
		return L"1";
	else if (path == L"Sound\\Invalid.wav")
		return L"2";
	else if (path == L"Sound\\Valid.mp3")
		return L"3";
	else if (path == L"Sound\\Enter.wav")
		return L"4";
	else if (path == L"Sound\\Change.mp3")
		return L"5";
	else if (path == L"Sound\\Coin.wav")
		return L"6";
	else if (path == L"Sound\\HighwayBackground.mp3")
		return L"7";
	else
		return L"";
}

//--------------Open and close file--------------
void Sound::openSound(std::wstring path) {
	std::wstring open = L"open \"" + path + L"\" type mpegvideo alias " + findAlias(path);
	mciSendString(open.c_str(), NULL, 0, NULL);
}
void Sound::closeSound(std::wstring alias) {
	std::wstring close = L"close " + alias;
	mciSendString(close.c_str(), NULL, 0, NULL);
}


//--------------Play and stop sound--------------
void Sound::repeatSound(std::wstring alias) {
	std::wstring repeat = L"play " + alias + L" repeat";
	mciSendString(repeat.c_str(), NULL, 0, NULL);
}
void Sound::pauseSound(std::wstring alias) {
	std::wstring pause = L"pause " + alias;
	mciSendString(pause.c_str(), NULL, 0, NULL);
}
void Sound::resumeSound(std::wstring alias) {
	std::wstring resume = L"resume " + alias;
	mciSendString(resume.c_str(), NULL, 0, NULL);
}

void Sound::setAudio(std::wstring alias, int volume) {
	std::wstring setAudio = L"setaudio " + alias + L" volume to " + std::to_wstring(volume * 10);
	mciSendString(setAudio.c_str(), NULL, 0, NULL);
}
void Sound::playSound(std::wstring alias) {
	std::wstring play = L"play " + alias;
	mciSendString(play.c_str(), NULL, 0, NULL);
}
//--------------Play background and effect sound--------------
void Sound::playBackgroundSound(int indexSound) {
	if (indexSound != currentIndexBackgroundSound) {
		closeSound(findAlias(BACKGROUND[currentIndexBackgroundSound]));
		firstTimePlaying = true;
	}
	if (indexSound == -1) {
		return;
	}
	std::wstring path = BACKGROUND[indexSound];
	std::wstring alias = findAlias(path);

	setAudio(alias, backgroundVolume);

	if (backgroundSound) {
		if (firstTimePlaying) {
			openSound(path);
			repeatSound(alias);
			backgroundPlaying = true;
			firstTimePlaying = false;
			currentIndexBackgroundSound = indexSound;
		}
		else {
			resumeSound(alias);
			backgroundPlaying = true;
		}
	}
	else {
		pauseSound(alias);
		backgroundPlaying = false;
	}
}

void Sound::playEffectSound(int indexSound) {
	std::wstring path = EFFECT[indexSound];
	std::wstring alias = findAlias(path);

	if (effectSound) {
		closeSound(alias);
		openSound(path);
		setAudio(alias, effectVolume);
		playSound(alias);
	}
}

void Sound::turnOffBackgroundSound() {
	backgroundSound = false;
	playBackgroundSound(currentIndexBackgroundSound);
}

void Sound::turnOnBackgroundSound() {
	backgroundSound = true;
	playBackgroundSound(currentIndexBackgroundSound);
}

void Sound::turnOffEffectSound() {
	effectSound = false;
}

void Sound::turnOnEffectSound() {
	effectSound = true;
}


//--------------Adjust volume--------------
bool Sound::turnUpBackgroundVolume() {
	if (backgroundVolume < 100 && backgroundVolume >= 0) {
		backgroundVolume += 20;
		playBackgroundSound(currentIndexBackgroundSound);
		return 1;
	}
	return 0;
}
bool Sound::turnDownBackgroundVolume() {
	if (backgroundVolume <= 100 && backgroundVolume > 0) {
		backgroundVolume -= 20;
		playBackgroundSound(currentIndexBackgroundSound);
		return 1;
	}
	return 0;
}
Sound* Sound::getInstance() {
	locker.lock();
	if (instance_ == nullptr) {
		instance_ = new Sound;
	}
	locker.unlock();
	return instance_;
}
bool Sound::turnUpEffectVolume() {
	if (effectVolume < 100 && effectVolume >= 0) {
		effectVolume += 20;
		return 1;
	}
	return 0;
}
bool Sound::turnDownEffectVolume() {
	if (effectVolume <= 100 && effectVolume > 0) {
		effectVolume -= 20;
		return 1;
	}
	return 0;
}

bool Sound::isBackgroundSoundOn() {
	return backgroundSound;
}

bool Sound::isEffectSoundOn() {
	return effectSound;
}

int Sound::getBackgroundVolume() {
	return backgroundVolume;
}

int Sound::getEffectVolume() {
	return effectVolume;
}
