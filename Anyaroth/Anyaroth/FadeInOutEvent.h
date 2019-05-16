#pragma once
#include "Event.h"
#include "Camera.h"
#include "CamEffectType.h"

class FadeInOutEvent : public Event
{
private:
	int _time, _timeOnEvent = 0;
	Camera* _cam;
	CamEffect _camEffect;

public:
	FadeInOutEvent(Camera* cam, int time, CamEffect type) : _cam(cam), _time(time), _camEffect(type) {}
	virtual ~FadeInOutEvent() {};

	virtual void update(double time);
	virtual void play();
};