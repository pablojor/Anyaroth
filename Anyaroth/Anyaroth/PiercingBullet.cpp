#include "PiercingBullet.h"



PiercingBullet::PiercingBullet(Game* game) : Bullet(game)
{
	_body->getBody()->GetFixtureList()->SetSensor(true);
}


PiercingBullet::~PiercingBullet()
{
}


void PiercingBullet::beginCollision(GameComponent * other, b2Contact* contact)
{
	if (other->getTag() == "Ground")
		_destroy = true;
	else if (getTag() == "Bullet" && (other->getTag() == "Enemy"))
		_collided = true;
	else if (getTag() == "EnemyBullet" && (other->getTag() == "Player"))
		_collided = true;

	contact->SetEnabled(false);
}

void PiercingBullet::update(double time)
{
	if (isActive())
	{
		double dist = _iniPos.distance(_transform->getPosition());

		if (_destroy)
		{
			_destroy = false;
			reset();
		}
		else if (dist < _range)
		{
			GameComponent::update(time);

			_body->getBody()->SetLinearVelocity(b2Vec2(_speed * cos(_transform->getRotation() * M_PI / 180.0), _speed * sin(_transform->getRotation() * M_PI / 180.0)));
			_aliveTime++;
		}
		
	}
}