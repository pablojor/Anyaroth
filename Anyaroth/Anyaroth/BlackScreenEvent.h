#pragma once
#include "Event.h"
#include "Camera.h"

class BlackScreenEvent : public Event
{
private:
	Camera* _cam;

public:
	BlackScreenEvent(Camera* cam) : _cam(cam) {}
	virtual ~BlackScreenEvent() {};

	virtual void update(double deltaTime) {}
	virtual void play();
};