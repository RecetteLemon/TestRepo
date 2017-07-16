#pragma once
#include "SingletonBase.h"
#include <map>

//fmod.hpp 추가!
#include "inc/fmod.hpp"

//lib링크
#pragma comment(lib, "lib/fmodex_vc.lib")

using namespace FMOD;

//채널 버퍼
#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 10

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER


class SoundManager : public SingletonBase <SoundManager>
{
private:
	map<string, int> mSoundIndex;
	map<string, int>::iterator miSoundIndex;

private:
	int soundIndexNum;
	System* _system;
	Sound** _sound;
	Channel** _channel;

public:
	HRESULT Init(void);
	void Release(void);
	void Update(void);

	void AddSound(string keyName, string soundName, bool bgm, bool loop);
	void Play(string keyName, float volume = 1.0f); // 0 ~ 255 -> 0.0 ~ 1.0
	void Stop(string keyName);
	void Pause(string keyName);
	void Resume(string keyName);
	void DeleteSound(string keyName);
	void DeleteAll();

	bool IsPlaySound(string keyName);

	bool IsPauseSound(string keyName);



	SoundManager();
	~SoundManager();
};

