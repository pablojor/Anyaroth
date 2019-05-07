#include "FitCameraEvent.h"

void FitCameraEvent::play()
{
	_cam->setWorldBounds(_xBound, _yBound);
	_cam->fitCamera({ _xBound, _yBound }, true);
	_finished = true;
}