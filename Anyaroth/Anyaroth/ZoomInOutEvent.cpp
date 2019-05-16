#include "ZoomInOutEvent.h"

void ZoomInOutEvent::update(double time)
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