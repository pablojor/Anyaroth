#include "MoveEvent.h"

MoveEvent::MoveEvent(BodyComponent* body, int dir, int speed, int xDestination):  _dir(dir), _speed(speed), _xDestination(xDestination)
{
	_myBody = body->getBody();
}

void MoveEvent::update(double time)
{
	if (_dir > 1)
	{
		if (_myBody->GetPosition().x > _xDestination)
		{
			_myBody->SetLinearVelocity(b2Vec2(0, _myBody->GetLinearVelocity().y));
			_finished = true;
		}
		else
			move();
	}
	else
	{
		if (_myBody->GetPosition().x > _xDestination)
		{
			_myBody->SetLinearVelocity(b2Vec2(0, _myBody->GetLinearVelocity().y));
			_finished = true;
		}
		else
			move();
	}
}

void MoveEvent::move()
{
	_myBody->SetLinearVelocity(b2Vec2(_dir * _speed, _myBody->GetLinearVelocity().y));
}