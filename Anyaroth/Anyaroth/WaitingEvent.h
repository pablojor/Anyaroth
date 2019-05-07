#pragma once
#include "Event.h"

class WaitingEvent : public Event
{
private:
	int _time, _timeWaiting = 0;

public:
	WaitingEvent(int time) : _time(time) {}

	virtual void update(const double& time);
	virtual void play() {}
};