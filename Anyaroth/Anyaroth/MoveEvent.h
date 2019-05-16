#pragma once
#include "Event.h"
#include "BodyComponent.h"

class MoveEvent : public Event
{
private:
	b2Body* _myBody;
	int _dir, _xDestination, _speed;

public:
	MoveEvent(BodyComponent* body, int dir, int speed, int xDestination);
	virtual ~MoveEvent() {};

	virtual void update(double time);
	void move();

	virtual void play() {}
};