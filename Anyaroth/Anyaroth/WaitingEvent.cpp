#include "WaitingEvent.h"

void WaitingEvent::update(double time)
{
	if (_timeWaiting > _time)
		_finished = true;
	else
		_timeWaiting += time;
}