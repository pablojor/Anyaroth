#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <map>

using namespace std;

class SoundManager
{
private:
	map<string, Mix_Chunk*> _soundFX;
	map<string, Mix_Music*> _music;
public:
	SoundManager();
	~SoundManager();

	void addSFX(const string& name, const string& fileName);
	void removeSFX(const string& name);

	void addMusic(const string& name, const string& fileName);
	void removeMusic(const string& name);

	void playSFX(const string& name, int channel = -1);

	/*void resumeSFX(const string& name);
	void pauseSFX(const string& name);
	void stopSFX(const string& name);		//Estos metodos no tendrian sentido con los efectos de sonido
	void resumeAllSFX();					//pero los dejo comentados por si alguien quiere que lo implemente
	void pauseAllSFX();						//en un futuro.
	void stopAllSFX();*/

	void playMusic(const string& name, bool loops = false);
	void resumeMusic();
	void pauseMusic();
	void stopMusic();

	void resumeAll();
	void pauseAll();

	int getGeneralVolume() const;
	int getMusicVolume() const;
	int getChannelVolume(int channel) const;
	void setGeneralVolume(float volumeRatio);
	void setChannelVolume(int channel, float volumeRatio);
	void setMusicVolume(float volumeRatio);
	void setSFXVolume(const string& name, float volumeRatio);
};