
#include "pch.h"

FMOD_SYSTEM* SoundManager::g_sound_system;

SoundManager* SoundManager::m_instance = nullptr;

SoundManager::SoundManager(const char* path, bool loop)
	:m_bool(false)
{
	if (loop) {
		FMOD_System_CreateSound(g_sound_system, path, FMOD_LOOP_NORMAL, 0, &m_sound);
	}
	else {
		FMOD_System_CreateSound(g_sound_system, path, FMOD_DEFAULT, 0, &m_sound);
	}

	m_channel = nullptr;
	m_volume = SOUND_DEFAULT;
}


SoundManager::SoundManager()
	:m_bool(false), m_channel(nullptr), m_volume(0), m_sound(nullptr)
{
	m_instance = GetInstance();

}

SoundManager::~SoundManager()
{
	FMOD_Sound_Release(m_sound);
	m_instance->FreeIntance();
}


int SoundManager::Init() 
{
	FMOD_System_Create(&g_sound_system);
	FMOD_System_Init(g_sound_system, 32, FMOD_INIT_NORMAL, NULL);

	return 0;
}

int SoundManager::Release() 
{
	FMOD_System_Close(g_sound_system);
	FMOD_System_Release(g_sound_system);

	return 0;
}


int SoundManager::play() 
{
	FMOD_System_PlaySound(g_sound_system, m_sound, NULL, false, &m_channel);

	return 0;
}

int SoundManager::pause() 
{
	FMOD_Channel_SetPaused(m_channel, true);

	return 0;
}

int SoundManager::resume() 
{
	FMOD_Channel_SetPaused(m_channel, false);

	return 0;
}

int SoundManager::stop() 
{
	FMOD_Channel_Stop(m_channel);

	return 0;
}

int SoundManager::volumeUp() 
{
	if (m_volume < SOUND_MAX) 
	{
		m_volume += SOUND_WEIGHT;
	}

	FMOD_Channel_SetVolume(m_channel, m_volume);

	return 0;
}

int SoundManager::volumeDown() 
{
	if (m_volume > SOUND_MIN) 
	{
		m_volume -= SOUND_WEIGHT;
	}

	FMOD_Channel_SetVolume(m_channel, m_volume);

	return 0;
}


int SoundManager::Update() 
{
	FMOD_Channel_IsPlaying(m_channel, &m_bool);

	if (m_bool) 
	{
		FMOD_System_Update(g_sound_system);
	}

	return 0;
}