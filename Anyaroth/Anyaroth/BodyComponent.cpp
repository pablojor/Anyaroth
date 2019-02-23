#include "BodyComponent.h"
#include "GameComponent.h"
#include "Game.h"

BodyComponent::BodyComponent(GameComponent * obj) : PhysicsComponent(obj)
{
	_transform = obj->getComponent<TransformComponent>();

	auto t = obj->getComponent<Texture>();
	
	_textW = (t->getW() / t->getNumCols());
	_textH = (t->getH() / t->getNumFils());

	_aX = _transform->getAnchor().getX();
	_aY = _transform->getAnchor().getY();

	_width = _textW / (M_TO_PIXEL * 2);
	_height = _textH / (M_TO_PIXEL * 2);

	_world = obj->getWorld();

	b2BodyDef _bodydef;
	_bodydef.type = b2_staticBody;
	_bodydef.position = b2Vec2((_transform->getPosition().getX() + _textW *(0.5-_aX)) / M_TO_PIXEL, (_transform->getPosition().getY() + _textH *(0.5-_aY) )/ M_TO_PIXEL);
	_bodydef.angle = 0.0;
	_body = _world->CreateBody(&_bodydef);

	_shape.SetAsBox(_width, _height);
	_fixture.shape = &_shape;
	_fixture.density = 1;
	_fixture.restitution = 0;
	_fixture.friction =1;
	

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
		_transform->setPosition(((double)_body->GetPosition().x*M_TO_PIXEL)-_textW*(0.5-_aX), ((double)_body->GetPosition().y*M_TO_PIXEL)-_textH*(0.5-_aY));
}


b2Body* BodyComponent::getBody()
{
	return _body;
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

double BodyComponent::getW()
{
	return _width;
}

double BodyComponent::getH()
{
	return _height;
}

//recive la categoria a la que pertenece y las categorias con las que colisiona (del enum _Category)
void BodyComponent::filterCollisions(uint16 ownCategory, uint16 collidesWith)
{
	_body->DestroyFixture(_body->GetFixtureList());

	_fixture.filter.categoryBits = ownCategory;
	_fixture.filter.maskBits = collidesWith;

	_body->CreateFixture(&_fixture);
}

