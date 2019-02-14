#include "BodyComponent.h"
#include "GameComponent.h"
#include "Game.h"

BodyComponent::BodyComponent(GameComponent * obj) : PhysicsComponent(obj)
{
	_transform = obj->getComponent<TransformComponent>();
	auto t = obj->getComponent<Texture>();
	_world = obj->getWorld();
	b2BodyDef _bodydef;
	_bodydef.type = b2_staticBody;
	_bodydef.position = b2Vec2(_transform->getPosition().getX()*(1/M_TO_PIXEL),_transform->getPosition().getY()*(1/M_TO_PIXEL));
	_bodydef.angle = 0.0;
	_body = _world->CreateBody(&_bodydef);
	b2PolygonShape shape;
	shape.SetAsBox((t->getW()/t->getNumCols()) *(1 / M_TO_PIXEL), (t->getH()/t->getNumFils()) *(1 / M_TO_PIXEL));
	_fixture.shape = &shape;
	_fixture.density = 1;
	_fixture.restitution = 0;
	_body->CreateFixture(&_fixture);
	_body->SetUserData(obj);
}

BodyComponent::~BodyComponent()
{
	_world->DestroyBody(_body);
}

void BodyComponent::update()
{
	_transform->setPosition((double)_body->GetPosition().x*M_TO_PIXEL, (double)_body->GetPosition().y*M_TO_PIXEL);
}


b2Body* BodyComponent::getBody()
{
	return _body;
}

