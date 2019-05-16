#pragma once
#include "Event.h"
#include "Game.h"

class PlaySoundEvent : public Event
{
private:
	Game* _game;
	string _sound;

public:
	PlaySoundEvent(Game* game, string sound) : _game(game), _sound(sound) {}
	virtual ~PlaySoundEvent() {};

	virtual void update(double deltaTime) {}
	virtual void play();
};