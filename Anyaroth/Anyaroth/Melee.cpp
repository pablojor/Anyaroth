#include "Melee.h"
#include "Enemy.h"
#include "Game.h"
#include <math.h>

Melee::Melee(Game * g, Vector2D offset) : GameComponent(g, "Melee") , _offset(offset){}


void Melee::meleeAttack(double x, double y, int dir)
{
	_dir = dir;

	if (_body == nullptr)
	{
		_body = new BodyComponent(this, x + _offset.getX() * dir, y + _offset.getY(), _w, _h);
		addComponent<BodyComponent>(_body);
	}
	else
		_body->setBody(this, x + _offset.getX() * dir, y + _offset.getY(), _w, _h);

	_body->filterCollisions(MELEE, ENEMIES);
	_body->getBody()->SetType(b2_kinematicBody);
	_body->getBody()->GetFixtureList()->SetSensor(true);

	_center = Vector2D(x, y);
	_r = y + _offset.getY() - _center.getY();
}

void Melee::beginCollision(GameComponent * other, b2Contact * contact)
{
	if (other->getTag() == "Enemy")
		static_cast<Enemy*>(other)->subLife(_damage);
}

void Melee::endMelee()
{
	_body->deleteBody();
}