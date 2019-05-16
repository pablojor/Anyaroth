#pragma once
#include "Event.h"
#include "Game.h"

class PlayMusicEvent : public Event
{
private:
	Game* _game;
	string _music;

public:
	PlayMusicEvent(Game* game, string music) : _game(game), _music(music) {}
	virtual ~PlayMusicEvent() {};

	virtual void update(double deltaTime) {}
	virtual void play();
};