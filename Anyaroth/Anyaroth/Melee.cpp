#include "Melee.h"
#include "Enemy.h"
#include "Game.h"
#include <math.h>

Melee::Melee(Game * g, Vector2D offset, Uint16 collidesWith, double damage, double w, double h, MeleeType id) : GameObject(g, "Melee") , _offset(offset), _collidesWith(collidesWith), _damage(damage), _w(w), _h(h), _id(id) {}

void Melee::meleeAttack(double x, double y, int dir)
{
	_dir = dir;

	if (_body == nullptr)
	{
		_body = new BodyComponent(this, x + _offset.getX() * _dir, y + _offset.getY(), _w, _h);
		addComponent<BodyComponent>(_body);
	}
	else if (!_body->getBody()->IsActive())
	{
		_body->getBody()->SetActive(true);
		_body->getBody()->SetTransform(b2Vec2((x + _offset.getX() * _dir) / M_TO_PIXEL, (y + _offset.getY()) / M_TO_PIXEL), 0);
	}


	_body->getBody()->SetType(b2_kinematicBody);
	_body->setW(_w);
	_body->setH(_h);
	_body->getBody()->GetFixtureList()->SetSensor(true);

	_body->filterCollisions(MELEE, _collidesWith);

	_center = Vector2D(x, y);
	_r = Vector2D(x + _offset.getX(), y + _offset.getY()).distance(_center);
}

void Melee::endMelee()
{
	if (_body->getBody() != nullptr && _body->getBody()->IsActive())
	{
		if (!_body->getBody()->GetWorld()->IsLocked())
			_body->getBody()->SetActive(false);
	}
}

void Melee::setCollisionSize(const Vector2D & size)
{
	_w = size.getX();
	_h = size.getY();
	if (_body != nullptr)
	{
		_body->setW(_w);
		_body->setH(_h);
		_body->getBody()->GetFixtureList()->SetSensor(true);

		_body->filterCollisions(MELEE, _collidesWith);
	}
}
