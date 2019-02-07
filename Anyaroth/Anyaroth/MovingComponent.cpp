#include "MovingComponent.h"

void MovingComponent::update()
{
	Vector2D pos = _transform->getPosition();
	double x = pos.getX();
	double y = pos.getY();

	_transform->setPosition(_dir.getX() + x, _dir.getY() + y);
}