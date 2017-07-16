#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
	: _system(NULL),
	_sound(NULL),
	_channel(NULL)
{
}


SoundManager::~SoundManager()
{
}

HRESULT SoundManager::Init(void)
{
	//사운드 시스템 형성
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//채널과 사운드는 동적할당(필수)
	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	memset(_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));


	soundIndexNum = 0;
	return S_OK;
}

void SoundManager::Release(void)
{
	DeleteAll();
}

void SoundManager::Update(void)
{

}

void SoundManager::AddSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[mSoundIndex.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[mSoundIndex.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[mSoundIndex.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[mSoundIndex.size()]);
		}
	}


	mSoundIndex.insert(make_pair(keyName, soundIndexNum));
	soundIndexNum++;
}

void SoundManager::Play(string keyName, float volume) // 0 ~ 255 -> 0.0 ~ 1.0
{
	for (miSoundIndex = mSoundIndex.begin(); miSoundIndex != mSoundIndex.end();)
	{
		if (miSoundIndex->first == keyName)
		{
			int tempIndexNum = miSoundIndex->second;
			_system->playSound(FMOD_CHANNEL_FREE, _sound[tempIndexNum], false, &_channel[tempIndexNum]);
			_channel[tempIndexNum]->setVolume(volume);

			break;
		}
		else
			miSoundIndex++;
	}
}

void SoundManager::Stop(string keyName)
{
	for (miSoundIndex = mSoundIndex.begin(); miSoundIndex != mSoundIndex.end();)
	{
		if (miSoundIndex->first == keyName)
		{
			int tempIndexNum = miSoundIndex->second;
			_channel[tempIndexNum]->stop();
			break;
		}
		else
			miSoundIndex++;
	}
}

void SoundManager::Pause(string keyName)
{
	for (miSoundIndex = mSoundIndex.begin(); miSoundIndex != mSoundIndex.end();)
	{
		if (miSoundIndex->first == keyName)
		{
			int tempIndexNum = miSoundIndex->second;
			_channel[tempIndexNum]->setPaused(true);
			break;
		}
		else
			miSoundIndex++;
	}
}

void SoundManager::Resume(string keyName)
{
	for (miSoundIndex = mSoundIndex.begin(); miSoundIndex != mSoundIndex.end();)
	{
		if (miSoundIndex->first == keyName)
		{
			int tempIndexNum = miSoundIndex->second;
			_channel[tempIndexNum]->setPaused(false);
			break;
		}
		else
			miSoundIndex++;
	}
}

bool SoundManager::IsPlaySound(string keyName)
{
	bool isPlay;

	for (miSoundIndex = mSoundIndex.begin(); miSoundIndex != mSoundIndex.end();)
	{
		if (miSoundIndex->first == keyName)
		{
			int tempIndexNum = miSoundIndex->second;
			_channel[tempIndexNum]->isPlaying(&isPlay);
			break;
		}
		else
			miSoundIndex++;
	}

	return isPlay;
}

bool SoundManager::IsPauseSound(string keyName)
{
	bool isPause;
	for (miSoundIndex = mSoundIndex.begin(); miSoundIndex != mSoundIndex.end();)
	{
		if (miSoundIndex->first == keyName)
		{
			int tempIndexNum = miSoundIndex->second;
			_channel[tempIndexNum]->getPaused(&isPause);
			break;
		}
		else
			miSoundIndex++;
	}
	return isPause;
}

void SoundManager::DeleteSound(string keyName)
{
	if (IsPlaySound(keyName))
	{
		Stop(keyName);
	}
	else
	{
		for (miSoundIndex = mSoundIndex.begin(); miSoundIndex != mSoundIndex.end();)
		{
			if (miSoundIndex->first == keyName)
			{
				int tempIndexNum = miSoundIndex->second;
				_sound[tempIndexNum]->release();

				break;
			}
			else
				++miSoundIndex;
		}
	}

}


void SoundManager::DeleteAll()
{
	for (miSoundIndex = mSoundIndex.begin(); miSoundIndex != mSoundIndex.end(); ++miSoundIndex)
	{
		int tempIndexNum = miSoundIndex->second;
		_sound[tempIndexNum]->release();
	}
}