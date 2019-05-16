#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{
	if (SDL_Init(SDL_INIT_AUDIO) == 0)
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
			cout << "No se ha iniciado el SoundManager de manera correcta: " << Mix_GetError() << endl;
}

SoundManager::~SoundManager()
{
	for (auto it = _soundFX.begin(); it != _soundFX.end(); it++)
		Mix_FreeChunk((*it).second);

	for (auto it = _music.begin(); it != _music.end(); it++)
		Mix_FreeMusic((*it).second);

	Mix_CloseAudio();
}

void SoundManager::addSFX(const string& name, const string& fileName)
{
	Mix_Chunk* fx = Mix_LoadWAV(fileName.c_str());
	if (fx != nullptr)
		_soundFX[name] = fx;
}

void SoundManager::removeSFX(const string& name)
{
	auto it = _soundFX.find(name);
	if (it != _soundFX.end())
	{
		Mix_FreeChunk((*it).second);
		_soundFX.erase(it);
	}
}

void SoundManager::addMusic(const string& name, const string& fileName)
{
	Mix_Music* mus = Mix_LoadMUS(fileName.c_str());
	if (mus != nullptr)
		_music[name] = mus;
}

void SoundManager::removeMusic(const string& name)
{
	auto it = _music.find(name);
	if (it != _music.end())
	{
		Mix_FreeMusic((*it).second);
		_music.erase(it);
	}
}

void SoundManager::playSFX(const string& name, int channel)
{
	if (_soundFX.find(name) != _soundFX.end())
		Mix_PlayChannel(channel, _soundFX[name], 0);
}

void SoundManager::playMusic(const string& name, bool loops)
{
	if (_music.find(name) != _music.end())
		Mix_PlayMusic(_music[name], loops ? -1 : 0);
}

void SoundManager::resumeMusic()
{
	if(Mix_PausedMusic())
		Mix_ResumeMusic();
}

void SoundManager::pauseMusic()
{
	if (!Mix_PausedMusic())
		Mix_PauseMusic();
}

void SoundManager::stopMusic()
{
	Mix_HaltMusic();
}

void SoundManager::resumeAll()
{
	Mix_Resume(-1);
}

void SoundManager::pauseAll()
{
	Mix_Pause(-1);
}

int SoundManager::getGeneralVolume() const
{
	return Mix_Volume(-1, -1);
}

int SoundManager::getMusicVolume() const
{
	return Mix_VolumeMusic(-1);
}

int SoundManager::getChannelVolume(int channel) const
{
	return Mix_Volume(channel, -1);
}

void SoundManager::setGeneralVolume(float volumeRatio)
{
	Mix_Volume(-1, MIX_MAX_VOLUME * volumeRatio);
}

void SoundManager::setChannelVolume(int channel, float volumeRatio)
{
	Mix_Volume(channel, MIX_MAX_VOLUME * volumeRatio);
}

void SoundManager::setMusicVolume(float volumeRatio)
{
	Mix_VolumeMusic(MIX_MAX_VOLUME * volumeRatio);
}

void SoundManager::setSFXVolume(const string& name, float volumeRatio)
{
	Mix_VolumeChunk(_soundFX[name], MIX_MAX_VOLUME * volumeRatio);
}