#pragma once
#pragma comment(lib, "winmm.lib")

#include <Windows.h>
#include <string>
#include <vector>
#include <mmsystem.h>
#include <iostream>
#include <mutex>

class Sound {
private:
    bool backgroundSound;
    bool effectSound;
    bool backgroundPlaying;
    bool firstTimePlaying;
    int backgroundVolume;
    int effectVolume;
    int currentIndexBackgroundSound;

    std::wstring findAlias(std::wstring path);

    void repeatSound(std::wstring alias);
    void playSound(std::wstring alias);
    void pauseSound(std::wstring alias);
    void resumeSound(std::wstring alias);
    void setAudio(std::wstring alias, int volume);
    void openSound(std::wstring path);
    void closeSound(std::wstring alias);

    static const std::vector<std::wstring> EFFECT;
    static const std::vector<std::wstring> BACKGROUND;

    static std::mutex locker;
protected:
    Sound() {
         backgroundSound = true;
         effectSound = true;
         backgroundPlaying = false;
         firstTimePlaying = true;
         backgroundVolume = 100;
         effectVolume = 100;
        currentIndexBackgroundSound = 0;
    };
    static Sound* instance_;

public:
    
    Sound(Sound& other) = delete;
   void operator=(const Sound& other ) = delete;
   
   enum class Background : char {
        BACKGROUND_MUSIC,
        HIGHWAY
    };
    enum class Effect : char {
        CAR_CRASH,
        INVALID,
        VALID,
        ENTER,
        CHANGE,
        COIN
    };

    static Sound* getInstance();

    void playBackgroundSound(int indexSound);
    void playEffectSound(int indexSound);

    void turnOffBackgroundSound();
    void turnOnBackgroundSound();
    void turnOffEffectSound();
    void turnOnEffectSound();

    bool turnUpBackgroundVolume();
    bool turnDownBackgroundVolume();

    bool turnUpEffectVolume();
    bool turnDownEffectVolume();

    bool isBackgroundSoundOn();
    bool isEffectSoundOn();

    int getBackgroundVolume();
    int getEffectVolume();
};
