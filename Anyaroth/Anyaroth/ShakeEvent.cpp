#include "ShakeEvent.h"

void ShakeEvent::update(double time)
{
	if (_timeOnEvent > _time)
		_finished = true;
	else
		_timeOnEvent += time;
}

void ShakeEvent::play()
{
	_cam->shake(_intensity, _time);
}