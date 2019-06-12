#include "SoundMangerDx9.h"

SoundManagerDx9* SoundManagerDx9::s_Instace = 0;
bool CSoundSwitch::IsExit = false;
bool CSoundSwitch::IsMute = false;

SoundManagerDx9* SoundManagerDx9::getInstance()
{
	if (s_Instace == 0)
	{
		s_Instace = new SoundManagerDx9();
	}
	return s_Instace;
}

void SoundManagerDx9::LoadSoundBuffer(const char* fileName, eSoundID eID, LPDIRECTSOUND8 _lpDSound)
{
	SoundBuffer* _soundbuffer = new SoundBuffer();
	_soundbuffer->LoadWaveToBuffer(_lpDSound, (char*)fileName);
	_soundbuffer->getSoundBuffer()->SetVolume(m_Volume);
	m_ListSoundBuffer[eID] = _soundbuffer;
}

void SoundManagerDx9::LoadAllSoundBuffer(LPDIRECTSOUND8 _lpDSound)
{
	this->LoadSoundBuffer("resources\\Sound\\background1.wav", eSoundID::SOUND_BACKGROUND_1, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\background2.wav", eSoundID::SOUND_BACKGROUND_2, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\background3.wav", eSoundID::SOUND_BACKGROUND_3, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\boss.wav", eSoundID::SOUND_BOSS, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\gameover.wav", eSoundID::SOUND_DEAD, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\explosion.wav", eSoundID::SOUND_EXPLOSION, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\flames.wav", eSoundID::SOUND_FLAMES, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\machinegun.wav", eSoundID::SOUND_MACHINE_GUN, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\climb.wav", eSoundID::SOUND_NINJA_CLIMB, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\collect.wav", eSoundID::SOUND_NINJA_COLLECT, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\hit.wav", eSoundID::SOUND_NINJA_HIT, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\hitted.wav", eSoundID::SOUND_NINJA_HITTED, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\jump.wav", eSoundID::SOUND_NINJA_JUMP, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\rocket.wav", eSoundID::SOUND_ROCKET, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\throwstar.wav", eSoundID::SOUND_THROW_STAR, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\windmilstar.wav", eSoundID::SOUND_WINDMIL_STAR, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\bossdead.wav", eSoundID::SOUND_BOSS_DEAD, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\logo.wav", eSoundID::SOUND_LOGO, _lpDSound);
}
SoundBuffer* SoundManagerDx9::getSoundBuffer(eSoundID eID)
{
	map<eSoundID, SoundBuffer*>::iterator i;
	i = m_ListSoundBuffer.find(eID);
	if (i == m_ListSoundBuffer.end())
		return 0;
	return i->second;
}

void SoundManagerDx9::SetVolume(long volume)
{
	if (volume < -10000)
		volume = -10000;
	if (volume > 0)
		volume = 0;
	this->m_Volume = volume;

	map<eSoundID, SoundBuffer*>::iterator i;
	for (i = m_ListSoundBuffer.begin(); i != m_ListSoundBuffer.end(); i++)
		i->second->getSoundBuffer()->SetVolume(m_Volume);
}
void SoundManagerDx9::SetMute(bool isMute)
{
	CSoundSwitch::IsMute = isMute;
	map<eSoundID, SoundBuffer*>::iterator i;
	if (isMute)
	{
		for (i = m_ListSoundBuffer.begin(); i != m_ListSoundBuffer.end(); i++)
			i->second->getSoundBuffer()->SetVolume(-10000);
	}
}
void SoundManagerDx9::UpVolume()
{
	if (m_Volume > -9900)
		m_Volume = -9900;
	m_Volume += 100;
	SetVolume(m_Volume);
}
void SoundManagerDx9::DownVolume()
{
	if (m_Volume < -9900)
		m_Volume = -9900;
	m_Volume -= 100;
	SetVolume(m_Volume);
}

void SoundManagerDx9::Release()
{
	map<eSoundID, SoundBuffer*>::iterator i;
	for (i = m_ListSoundBuffer.begin(); i != m_ListSoundBuffer.end(); i++)
	{
		i->second->Release();
		SAFE_DELETE(i->second);
	}
	m_ListSoundBuffer.clear();
}