#include "BodyComponent.h"
#include "GameComponent.h"

BodyComponent::BodyComponent(GameComponent * obj) : PhysicsComponent(obj)
{
	_world = obj->getWorld();
	b2BodyDef _bodydef;
	_bodydef.type = b2_staticBody;
	_bodydef.position = b2Vec2(0,0);
	_bodydef.angle = 0.0;
	_body = _world->CreateBody(&_bodydef);
	b2PolygonShape shape;
	shape.SetAsBox(1, 1);
	_fixture.shape = &shape;
	_fixture.density = 1;
	_body->CreateFixture(&_fixture);
	_body->SetUserData(obj);
}

BodyComponent::~BodyComponent()
{
}

void BodyComponent::update()
{
}


b2Body* BodyComponent::getBody()
{
	return _body;
}

