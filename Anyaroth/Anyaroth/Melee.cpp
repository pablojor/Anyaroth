#include "Melee.h"
#include "Enemy.h"
#include "Game.h"
#include <math.h>

Melee::Melee(Game * g, Vector2D offset, Uint16 collidesWith, double damage, double w, double h) : GameComponent(g, "Melee") , _offset(offset), _collidesWith(collidesWith), _damage(damage), _w(w), _h(h) {}


void Melee::meleeAttack(double x, double y, int dir)
{
	_dir = dir;

	if (_body == nullptr)
	{
		_body = new BodyComponent(this, x + _offset.getX() * _dir, y + _offset.getY(), _w, _h);
		addComponent<BodyComponent>(_body);
	}
	else
		_body->setBody(this, x + _offset.getX() * _dir, y + _offset.getY(), _w, _h);

	_body->filterCollisions(MELEE, _collidesWith);
	_body->getBody()->SetType(b2_kinematicBody);
	_body->getBody()->GetFixtureList()->SetSensor(true);

	_center = Vector2D(x, y);
	_r = Vector2D(x + _offset.getX(), y + _offset.getY()).distance(_center);
}

void Melee::endMelee()
{
	_body->deleteBody();
}