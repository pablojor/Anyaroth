#include "waitEvent.h"



waitEvent::waitEvent(int time) : _time(time)
{
}

void waitEvent::update(const double& time)
{
	if (_timeWaiting > _time)
		_finished = true;
	else
		_timeWaiting += time;
}