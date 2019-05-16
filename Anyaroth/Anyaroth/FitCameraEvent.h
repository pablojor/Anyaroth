#pragma once
#include "Event.h"
#include "Camera.h"

class FitCameraEvent : public Event
{
private:
	Camera* _cam;
	double _xBound, _yBound;

public:
	FitCameraEvent(Camera* cam, double x, double y) : _cam(cam), _xBound(x), _yBound(y) {}
	virtual ~FitCameraEvent() {};

	virtual void update(double deltaTime) {}
	virtual void play();
};