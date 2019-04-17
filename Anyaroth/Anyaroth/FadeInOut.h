#pragma once
#include "Event.h"
#include "Camera.h"
#include "CamEffectType.h"

class FadeInOut : public Event
{
private:
	int _time, _timeOnEvent = 0;
	Camera* _cam;
	CamEffect _camEffect;

	public:
		FadeInOut(Camera* cam, int time, CamEffect type);

		virtual void update(const double& time);
		virtual void play();
};

