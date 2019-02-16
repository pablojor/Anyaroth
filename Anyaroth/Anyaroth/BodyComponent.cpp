#include "BodyComponent.h"
#include "GameComponent.h"
#include "Game.h"

BodyComponent::BodyComponent(GameComponent * obj) : PhysicsComponent(obj)
{
	_transform = obj->getComponent<TransformComponent>();
	auto t = obj->getComponent<Texture>();
	textW = (t->getW() / t->getNumCols())*RESOLUTION, textH = (t->getH() / t->getNumFils())*RESOLUTION;
	aX = _transform->getAnchor().getX(), aY = _transform->getAnchor().getY();
	_world = obj->getWorld();
	b2BodyDef _bodydef;
	_bodydef.type = b2_staticBody;
	_bodydef.position = b2Vec2((_transform->getPosition().getX() + textW *(0.5-aX)) / M_TO_PIXEL, (_transform->getPosition().getY() + textH *(0.5-aY) )/ M_TO_PIXEL);
	_bodydef.angle = 0.0;
	_body = _world->CreateBody(&_bodydef);
	b2PolygonShape shape;
	shape.SetAsBox(((textW)) / (M_TO_PIXEL*2), ((textH)) / (M_TO_PIXEL * 2));
	_fixture.shape = &shape;
	_fixture.density = 1;
	_fixture.restitution = 0;
	_fixture.friction = 1;
	_body->CreateFixture(&_fixture);
	_body->SetUserData(obj);
}

BodyComponent::~BodyComponent()
{
	_world->DestroyBody(_body);
}

void BodyComponent::update()
{

	if (_body->GetType() != b2_staticBody)
		_transform->setPosition(((double)_body->GetPosition().x*M_TO_PIXEL)-textW*(0.5-aX), ((double)_body->GetPosition().y*M_TO_PIXEL)-textH*(0.5-aY));
}


b2Body* BodyComponent::getBody()
{
	return _body;
}

