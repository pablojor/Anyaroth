#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

using namespace std;

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void addSFX(string name, string fileName);
	void removeSFX(string name);

	void addMusic(string name, string fileName);
	void removeMusic(string name);

	void playSFX(string name);
	void resumeSFX();
	void pauseSFX();

	void playMusic(string name);
	void resumeMusic();
	void pauseMusic();
	void stopMusic();

	void getVolume();
	void setVolume(float volume);
};

