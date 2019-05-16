#include "FadeInOutEvent.h"

void FadeInOutEvent::update(double time)
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