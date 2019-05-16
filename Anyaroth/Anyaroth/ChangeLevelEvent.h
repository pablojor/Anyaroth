#pragma once
#include "Event.h"
#include "Player.h"

class ChangeLevelEvent : public Event
{
private:
	Player* _player;

public:
	ChangeLevelEvent(Player* player) : _player(player) {}
	virtual ~ChangeLevelEvent() {};

	virtual void play();
	virtual void update(double deltaTime) {}
};