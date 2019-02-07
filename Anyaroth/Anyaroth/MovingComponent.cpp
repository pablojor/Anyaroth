#include "MovingComponent.h"

void MovingComponent::update()
{
	double x = _dir.getX() * _velocity + _transform->getPosition().getX();
	double y = _dir.getY() * _velocity + _transform->getPosition().getY();

	_transform->setPosition(x, y);
}