#pragma once
#include <fmod.h>

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f

class SoundManager
{
private:
	static SoundManager* m_instance;
public:
	static SoundManager* GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new SoundManager();
		}
		return m_instance;
	}
private:
	static FMOD_SYSTEM* g_sound_system;

	FMOD_SOUND* m_sound;
	FMOD_CHANNEL* m_channel;

	float m_volume;
	FMOD_BOOL m_bool;
public:
	SoundManager();
	SoundManager(const char* path, bool loop);
	~SoundManager();

	static int Init();
	static int Release();

	int play();
	int pause();
	int resume();
	int stop();
	int volumeUp();
	int volumeDown();
	int Update();

public:
	static void FreeIntance()
	{
		if (m_instance != nullptr)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

};

