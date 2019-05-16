#include "BodyComponent.h"
#include "GameObject.h"
#include "Game.h"

BodyComponent::BodyComponent(GameObject * obj) : PhysicsComponent(obj)
{
	_transform = obj->getComponent<TransformComponent>();
	auto t = obj->getComponent<Texture>();

	
	if (t != nullptr)
	{
		_textW = (t->getW() / t->getNumCols());
		_textH = (t->getH() / t->getNumFils());
	}
	else
	{
		_textW = 32;
		_textH = 32;
	}

	_aX = _transform->getAnchor().getX();
	_aY = _transform->getAnchor().getY();

	_width = _textW / (M_TO_PIXEL * 2);
	_height = _textH / (M_TO_PIXEL * 2);

	_world = obj->getWorld();

	b2BodyDef _bodydef;
	_bodydef.type = b2_staticBody;
	_bodydef.position = b2Vec2((_transform->getPosition().getX() + _textW * (0.5 - _aX)) / M_TO_PIXEL, (_transform->getPosition().getY() + _textH * (0.5 - _aY)) / M_TO_PIXEL);
	_bodydef.angle = 0.0;
	_body = _world->CreateBody(&_bodydef);

	_shape.SetAsBox(_width, _height);
	_fixture.shape = &_shape;
	_fixture.density = 1;
	_fixture.restitution = 0;
	_fixture.friction = 0.001;

	_body->CreateFixture(&_fixture)->SetUserData(obj);
	_body->SetUserData(obj);
}

BodyComponent::BodyComponent(GameObject * obj, double x, double y, double w, double h) : PhysicsComponent(obj)
{
	_world = obj->getWorld();

	b2BodyDef _bodydef;
	_bodydef.type = b2_dynamicBody;
	_bodydef.position = b2Vec2(x/ M_TO_PIXEL, y / M_TO_PIXEL);
	_bodydef.angle = 0.0;
	_body = _world->CreateBody(&_bodydef);

	_shape.SetAsBox(w / M_TO_PIXEL, h / M_TO_PIXEL);
	_fixture.shape = &_shape;
	_fixture.density = 1;
	_fixture.restitution = 0;
	_fixture.friction = 0.001;

	_body->CreateFixture(&_fixture);
	_body->SetUserData(obj);
	_body->SetFixedRotation(true);
}

BodyComponent::~BodyComponent()
{
	if (_body != nullptr)
		_world->DestroyBody(_body);
}

void BodyComponent::update(double deltaTime)
{
	if (_body!=nullptr && (_body->GetType() != b2_staticBody && _transform != nullptr))
		_transform->setPosition(((double)_body->GetPosition().x*M_TO_PIXEL) - _textW * (0.5 - _aX), ((double)_body->GetPosition().y*M_TO_PIXEL) - _textH * (0.5 - _aY));
}

void BodyComponent::setW(double w)
{
	_body->DestroyFixture(_body->GetFixtureList());

	_width = w / (M_TO_PIXEL * 2);
	
	_shape.SetAsBox(_width, _height);
	_body->CreateFixture(&_fixture);
}

void BodyComponent::setH(double h)
{
	_body->DestroyFixture(_body->GetFixtureList());
	
	_height = h / (M_TO_PIXEL * 2);
	
	_shape.SetAsBox(_width, _height);
	_body->CreateFixture(&_fixture);
}

void BodyComponent::setBody(GameObject * obj, double x, double y, double w, double h)
{
	b2BodyDef _bodydef;
	_bodydef.type = b2_dynamicBody;
	_bodydef.position = b2Vec2(x / M_TO_PIXEL, y / M_TO_PIXEL);
	_bodydef.angle = 0.0;
	_body = _world->CreateBody(&_bodydef);

	_shape.SetAsBox(w / M_TO_PIXEL, h / M_TO_PIXEL);
	_fixture.shape = &_shape;
	_fixture.density = 1;
	_fixture.restitution = 0;
	_fixture.friction = 0.001;

	_body->CreateFixture(&_fixture);
	_body->SetUserData(obj);
	_body->SetFixedRotation(true);
}

void BodyComponent::deleteBody()
{
	_world->DestroyBody(_body);
	_body = nullptr;
}

void BodyComponent::moveShape(const b2Vec2 & Center)
{
	_body->DestroyFixture(_body->GetFixtureList());
	_shape.SetAsBox(_width, _height,Center,0);
	_body->CreateFixture(&_fixture);
}

void BodyComponent::addCricleShape(const b2Vec2 & Center, float radius, uint16 ownCategory, uint16 collidesWith)
{
	b2CircleShape* circulo = new b2CircleShape();
	circulo->m_p.Set(Center.x, Center.y);
	circulo->m_radius = radius;

	b2FixtureDef* fixt = new b2FixtureDef();
	fixt->restitution = 0;
	fixt->shape = circulo;
	fixt->density = 1;
	fixt->friction = 400;
	fixt->filter.categoryBits = ownCategory;
	fixt->filter.maskBits = collidesWith;

	_body->CreateFixture(fixt);

	delete fixt;
	delete circulo;
}

//recive la categoria a la que pertenece y las categorias con las que colisiona (del enum _Category)
void BodyComponent::filterCollisions(uint16 ownCategory, uint16 collidesWith, int groupIndex)
{
	auto fixture = _body->GetFixtureList();

	while (fixture != nullptr)
	{
		b2Filter filter = fixture->GetFilterData();

		filter.categoryBits = ownCategory;
		filter.maskBits = collidesWith;
		filter.groupIndex = groupIndex;

		fixture->SetFilterData(filter);

		fixture = fixture->GetNext();
	}
}

void BodyComponent::addFixture(b2FixtureDef* fixture, void* data)
{
	_body->CreateFixture(fixture)->SetUserData(data);
}