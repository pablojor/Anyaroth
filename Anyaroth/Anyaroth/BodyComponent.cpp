#include "BodyComponent.h"

BodyComponent::BodyComponent(GameComponent * obj) : PhysicsComponent(obj)
{
	_bodydef.type = _bodyType;
	_bodydef.position = _position;
	_bodydef.angle = _angle;
	_body = _world->CreateBody(&_bodydef);
}

BodyComponent::~BodyComponent()
{
}

void BodyComponent::update()
{
}

b2BodyDef BodyComponent::getBodyDef()
{
	return _bodydef;
}

b2Body* BodyComponent::getBody()
{
	return _body;
}