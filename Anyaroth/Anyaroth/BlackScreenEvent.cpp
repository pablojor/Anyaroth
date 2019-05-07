#include "BlackScreenEvent.h"

void BlackScreenEvent::play()
{
	_cam->setCameraAlpha(0);
	_finished = true;
}