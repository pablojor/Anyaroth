#include "BoxCollider.h"

void BoxCollider::update()
{
	_collider.x = _transform->getPosition().getX();
	_collider.y = _transform->getPosition().getY();
	_collider.w = _size.getX() * _transform->getScale().getX();
	_collider.h = _size.getY() * _transform->getScale().getY();
}