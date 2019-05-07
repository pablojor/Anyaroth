#pragma once
#include "Event.h"
#include "Camera.h"
#include "CamEffectType.h"

class ZoomInOutEvent : public Event
{
private:
	int _time, _timeOnEvent = 0;
	Camera* _cam;
	CamEffect _camEffect;

public:
	ZoomInOutEvent(Camera* cam, int time, CamEffect type) : _cam(cam), _time(time), _camEffect(type) {}

	virtual void update(const double& time);
	virtual void play() {}
};