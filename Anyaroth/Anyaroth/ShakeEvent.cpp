#include "ShakeEvent.h"


ShakeEvent::ShakeEvent(Camera* cam, int time, int intesity) : _cam(cam), _time (time), _intensity(intesity)
{
}

void ShakeEvent::update(const double& time)
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