#include "WaitingEvent.h"

WaitingEvent::WaitingEvent(int time) : _time(time)
{

}

void WaitingEvent::update(const double& time)
{
	if (_timeWaiting > _time)
		_finished = true;
	else
		_timeWaiting += time;
}