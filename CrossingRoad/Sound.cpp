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
	L"Sound\\Coin.wav",
	L"Sound\\Bubble.mp3",
	L"Sound\\Duck.mp3",
	L"Sound\\LogJump.mp3",
	L"Sound\\WaterSplash.wav",
	L"Sound\\Portal.mp3",
	L"Sound\\Hit.wav",
	L"Sound\\EndSoundWinterMap.mp3",
	L"Sound\\Train.mp3",
	L"Sound\\Typing.mp3",
	L"Sound\\Chicken.mp3",
	L"Sound\\Dinosaur.mp3",
	L"Sound\\CatMeow.mp3"
};
const std::vector<std::wstring> Sound::BACKGROUND = {
	L"Sound\\BackgroundMusic.mp3",
	L"Sound\\HighwayBackground.mp3",
	L"Sound\\ChristmasAmbient.mp3"
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
	else if (path == L"Sound\\ChristmasAmbient.mp3")
		return L"8";
	else if (path == L"Sound\\Bubble.mp3")
		return L"9";
	else if (path == L"Sound\\Duck.mp3")
		return L"10";
	else if (path == L"Sound\\LogJump.mp3")
		return L"11";
	else if (path == L"Sound\\WaterSplash.wav")
		return L"12";
	else if (path == L"Sound\\Portal.mp3")
		return L"13";
	else if (path == L"Sound\\Hit.wav")
		return L"14";
	else if (path == L"Sound\\EndSoundWinterMap.mp3")
		return L"15";
	else if (path == L"Sound\\Train.mp3")
		return L"16";
	else if (path == L"Sound\\Typing.mp3")
		return L"17";
	else if (path == L"Sound\\Chicken.mp3")
		return L"18";
	else if (path == L"Sound\\Dinosaur.mp3")
		return L"19";
	else if (path == L"Sound\\CatMeow.mp3")
		return L"20";
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
	if (indexSound != setting.currentIndexBackgroundSound) {
		closeSound(findAlias(BACKGROUND[setting.currentIndexBackgroundSound]));
		setting.firstTimePlaying = true;
	}
	if (indexSound == -1) {
		return;
	}
	std::wstring path = BACKGROUND[indexSound];
	std::wstring alias = findAlias(path);

	setAudio(alias, setting.backgroundVolume);

	if (setting.backgroundSound) {
		if (setting.firstTimePlaying) {
			openSound(path);
			repeatSound(alias);
			setting.backgroundPlaying = true;
			setting.firstTimePlaying = false;
			setting.currentIndexBackgroundSound = indexSound;
		}
		else {
			resumeSound(alias);
			setting.backgroundPlaying = true;
		}
	}
	else {
		pauseSound(alias);
		setting.backgroundPlaying = false;
	}
}

void Sound::playEffectSound(int indexSound) {
	std::wstring path = EFFECT[indexSound];
	std::wstring alias = findAlias(path);

	if (setting.effectSound) {
		closeSound(alias);
		openSound(path);
		setAudio(alias, setting.effectVolume);
		playSound(alias);
	}
}

void Sound::turnOffBackgroundSound() {
	setting.backgroundSound = false;
	playBackgroundSound(setting.currentIndexBackgroundSound);
}

void Sound::turnOnBackgroundSound() {
	setting.backgroundSound = true;
	playBackgroundSound(setting.currentIndexBackgroundSound);
}

void Sound::turnOffEffectSound() {
	setting.effectSound = false;
}

void Sound::turnOnEffectSound() {
	setting.effectSound = true;
}


//--------------Adjust volume--------------
bool Sound::turnUpBackgroundVolume() {
	if (setting.backgroundVolume < 100 && setting.backgroundVolume >= 0) {
		setting.backgroundVolume += 20;
		playBackgroundSound(setting.currentIndexBackgroundSound);
		return 1;
	}
	return 0;
}
bool Sound::turnDownBackgroundVolume() {
	if (setting.backgroundVolume <= 100 && setting.backgroundVolume > 0) {
		setting.backgroundVolume -= 20;
		playBackgroundSound(setting.currentIndexBackgroundSound);
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
	if (setting.effectVolume < 100 && setting.effectVolume >= 0) {
		setting.effectVolume += 20;
		return 1;
	}
	return 0;
}
bool Sound::turnDownEffectVolume() {
	if (setting.effectVolume <= 100 && setting.effectVolume > 0) {
		setting.effectVolume -= 20;
		return 1;
	}
	return 0;
}

void Sound::pauseBackgroundSound() {
	pauseSound(findAlias(BACKGROUND[setting.currentIndexBackgroundSound]));
	setting.backgroundPlaying = false;
}

void Sound::resumeBackgroundSound() {
	resumeSound(findAlias(BACKGROUND[setting.currentIndexBackgroundSound]));
	setting.backgroundPlaying = true;
	
}

void Sound::pauseEffectSound() {
	for (int i = 0; i < EFFECT.size(); i++) {
		pauseSound(findAlias(EFFECT[i]));
	}
}

void Sound::resumeEffectSound() {
	for (int i = 0; i < EFFECT.size(); i++) {
		resumeSound(findAlias(EFFECT[i]));
	}
}

bool Sound::isBackgroundSoundOn() {
	return setting.backgroundSound;
}

bool Sound::isEffectSoundOn() {
	return setting.effectSound;
}

int Sound::getBackgroundVolume() {
	return setting.backgroundVolume;
}

int Sound::getEffectVolume() {
	return setting.effectVolume;
}

void Sound::playCharacterSound(int playerType) {
	if(playerType == 0)
		playEffectSound((int)Effect::DUCK);
	else if (playerType == 1)
		playEffectSound((int)Effect::CHICKEN);
	else if (playerType == 2)
		playEffectSound((int)Effect::ENTER);
	else if (playerType == 3)
		playEffectSound((int)Effect::CAT);
	else if (playerType == 4)
		playEffectSound((int)Effect::DINOSAUR);
}