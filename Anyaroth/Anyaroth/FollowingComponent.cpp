#include "FollowingComponent.h"
#include "GameComponent.h"
#include <iostream>

FollowingComponent::FollowingComponent(GameComponent* obj, GameComponent* other) : PhysicsComponent(obj)
{
	_transformOther = other->getComponent<TransformComponent>();
	_transform = obj->getComponent<TransformComponent>();
	_other = other;
	_offset = {0,0};
}

void FollowingComponent::update(const double& deltaTime)
{
	double x = _transformOther->getPosition().getX() + _offset.getX();
	double y = _transformOther->getPosition().getY() + _offset.getY();
	_transform->setPosition(x, y);
}