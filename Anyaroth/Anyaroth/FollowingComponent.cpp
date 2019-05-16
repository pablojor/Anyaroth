#include "FollowingComponent.h"
#include "GameObject.h"
#include "Game.h"
#include <iostream>

FollowingComponent::FollowingComponent(GameObject* obj, GameObject* other) : PhysicsComponent(obj)
{
	_transformOther = other->getComponent<TransformComponent>();
	_transform = obj->getComponent<TransformComponent>();
	_body = obj->getComponent<BodyComponent>();
	_other = other;
	_offset = {0,0};
}

void FollowingComponent::update(double deltaTime)
{
	double x = _transformOther->getPosition().getX() + _offset.getX();
	double y = _transformOther->getPosition().getY() + _offset.getY();
	_transform->setPosition(x, y);
	if (_body != nullptr)
		_body->getBody()->SetTransform(b2Vec2(x / M_TO_PIXEL, y / M_TO_PIXEL), 0);
}