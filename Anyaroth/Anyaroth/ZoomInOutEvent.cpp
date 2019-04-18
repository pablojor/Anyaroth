#include "ZoomInOutEvent.h"

ZoomInOutEvent::ZoomInOutEvent(Camera* cam, int time, CamEffect type) : _cam(cam), _time(time), _camEffect(type)
{
}

void ZoomInOutEvent::update(const double& time)
{
	if (_timeOnEvent > _time)
		_finished = true;
	else
	{
		if (_camEffect == CamEffect::ZoomIn)
			_cam->zoomIn();
		else
			_cam->zoomOut();
		_timeOnEvent += time;
	}
}