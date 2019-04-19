#pragma once

#include "Event.h"

class waitEvent : public Event
{
	private:

		int _time, _timeWaiting = 0;
	public:
		waitEvent(int time);

		virtual void update(const double& time);

		virtual void play() {};
};

