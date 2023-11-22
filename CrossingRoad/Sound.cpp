#include "Sound.h"
#include <Windows.h>
#include <string.h>
#include <iostream>
#include <string>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

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
	L"Sound\\BackgroundMusic.mp3"
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
	else if ( path == L"Sound\\Enter.wav")
		return L"4";
	else if (path == L"Sound\\Change.mp3")
		return L"5";
	else if(path == L"Sound\\Coin.wav")
		return L"6",
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
void Sound::playBackgroundSound(Sound::SoundSetting& soundSetting,int preIndexSound, int indexSound) {
	if (preIndexSound != -1) {
		closeSound(findAlias(BACKGROUND[preIndexSound]));
	}
	std::wstring path = BACKGROUND[indexSound];
	std::wstring alias = findAlias(path);
	if (soundSetting.backgroundSound) {
		if (soundSetting.firstTimePlaying) {
			openSound(path);
			setAudio(alias, soundSetting.backgroundVolume);
			repeatSound(alias);
			soundSetting.backgroundPlaying = true;
			soundSetting.firstTimePlaying = false;
			soundSetting.currentIndexBackgroundSound = indexSound;
		}
		else {
			resumeSound(alias);
			soundSetting.backgroundPlaying = true;
		}
	}
	else {
		pauseSound(alias);
		soundSetting.backgroundPlaying = false;
	}
}
void Sound::playEffectSound(Sound::SoundSetting& soundSetting, int indexSound) {
	std::wstring path = EFFECT[indexSound];
	std::wstring alias = findAlias(path);

	if (soundSetting.effectSound) {
		closeSound(alias);
		openSound(path);
		setAudio(alias, soundSetting.effectVolume);
		playSound(alias);
	}
}

void Sound::turnOffBackgroundSound(Sound::SoundSetting& soundSetting,int indexSound) {
	soundSetting.backgroundSound = false;
	playBackgroundSound(soundSetting, -1, indexSound);
}

void Sound::turnOnBackgroundSound(Sound::SoundSetting& soundSetting,int indexSound) {
	soundSetting.backgroundSound = true;
	playBackgroundSound(soundSetting, -1, indexSound);
}

void Sound::turnOffEffectSound(Sound::SoundSetting& soundSetting) {
	soundSetting.effectSound = false;
}

void Sound::turnOnEffectSound(Sound::SoundSetting& soundSetting) {
	soundSetting.effectSound = true;
}


//--------------Adjust volume--------------
bool Sound::turnUpBackgroundVolume(SoundSetting& soundSetting) {
	if (soundSetting.backgroundVolume < 100 && soundSetting.backgroundVolume >= 0) {
		soundSetting.backgroundVolume += 20;
		for (auto i: BACKGROUND) {
			std::wstring volumeUp = L"setaudio " + findAlias(i) + L" volume to " + std::to_wstring(soundSetting.backgroundVolume * 10);
			mciSendString(volumeUp.c_str(), NULL, 0, NULL);
		}
		return 1;
	}
	return 0;
}
bool Sound::turnDownBackgroundVolume(SoundSetting& soundSetting) {
	if (soundSetting.backgroundVolume <= 100 && soundSetting.backgroundVolume > 0) {
		soundSetting.backgroundVolume -= 20;
		for (auto i : BACKGROUND) {
			std::wstring volumeDown = L"setaudio " + findAlias(i) + L" volume to " + std::to_wstring(soundSetting.backgroundVolume * 10);
			mciSendString(volumeDown.c_str(), NULL, 0, NULL);
		}
		return 1;
	}
	return 0;
}
bool Sound::turnUpEffectVolume(SoundSetting& soundSetting) {
	if (soundSetting.effectVolume < 100 && soundSetting.effectVolume >= 0) {
		soundSetting.effectVolume += 20;
		return 1;
	}
	return 0;
}
bool Sound::turnDownEffectVolume(SoundSetting& soundSetting) {
	if (soundSetting.effectVolume <= 100 && soundSetting.effectVolume > 0) {
		soundSetting.effectVolume -= 20;
		for (auto i : EFFECT) {
			std::wstring volumeDown = L"setaudio " + findAlias(i) + L" volume to " + std::to_wstring(soundSetting.effectVolume * 10);
			mciSendString(volumeDown.c_str(), NULL, 0, NULL);
		}
		return 1;
	}
	return 0;
}
