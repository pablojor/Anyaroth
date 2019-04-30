#include "FadeInOutEvent.h"



FadeInOutEvent::FadeInOutEvent(Camera* cam, int time, CamEffect type) : _cam(cam), _time(time), _camEffect(type)
{
}


void FadeInOutEvent::update(const double& time)
{
	if (_timeOnEvent > _time)
		_finished = true;
	else
		_timeOnEvent += time;
}

void FadeInOutEvent::play()
{
	if (_camEffect == CamEffect::FadeIn)
		_cam->fadeIn(_time);
	else
		_cam->fadeOut(_time);
}