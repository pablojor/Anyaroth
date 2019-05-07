#include "WaitingEvent.h"

void WaitingEvent::update(const double& time)
{
	if (_timeWaiting > _time)
		_finished = true;
	else
		_timeWaiting += time;
}