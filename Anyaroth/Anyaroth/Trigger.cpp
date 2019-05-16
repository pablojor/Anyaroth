#include "Trigger.h"
#include "Game.h"


Trigger::Trigger(Game* game, int xPos, int yPos) : GameObject(game, ""), _collidesWith(PLAYER)
{
	_transform = addComponent<TransformComponent>();
	_transform->setPosition(xPos, yPos);

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_kinematicBody);
	_body->filterCollisions(OBJECTS, PLAYER);
	_body->setH(800);
	_body->getBody()->GetFixtureList()->SetSensor(true);
}

Trigger::~Trigger()
{
	_onTriggerEnter = nullptr;
	_onTriggerExit = nullptr;
	_onTriggerUpdate = nullptr;
}

void Trigger::update(double deltaTime)
{
	_body->getBody()->SetAwake(true);
	GameObject::update(deltaTime);

	if (_triggered)
	{
		if (_onTriggerUpdate != nullptr)
			_onTriggerUpdate();
	}
}

void Trigger::beginCollision(GameObject * other, b2Contact * contact)
{
	if (other->isPlayer() && !_triggered)
	{
		_triggered = true;
		if (_onTriggerEnter != nullptr)
			_onTriggerEnter();
	}
}

void Trigger::endCollision(GameObject * other, b2Contact * contact)
{
	if (other->isPlayer() && _triggered)
	{
		_triggered = false;
		if (_onTriggerExit != nullptr)
			_onTriggerExit();
	}
}

void Trigger::onTriggerEnter(function<void()> func)
{
	_onTriggerEnter = func;
}

void Trigger::onTriggerExit(function<void()> func)
{
	_onTriggerExit = func;
}

void Trigger::onTriggerUpdate(function<void()> func)
{
	_onTriggerUpdate = func;
}

void Trigger::setPosition(int xPos, int yPos)
{
	_body->getBody()->SetTransform({ (float32)(xPos / M_TO_PIXEL), (float32)(yPos / M_TO_PIXEL) }, 0);
}

void Trigger::setCollisionFilters(uint16 collidesWith)
{
	_collidesWith = collidesWith;
	_body->filterCollisions(OBJECTS, _collidesWith);
}