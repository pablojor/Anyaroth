#include "PiercingBullet.h"

PiercingBullet::PiercingBullet(Game* game) : Bullet(game)
{
}

PiercingBullet::~PiercingBullet()
{
}

void PiercingBullet::beginCollision(GameObject * other, b2Contact* contact)
{
	if (other->getTag() == "Suelo")
		_destroy = true;
	else if (getTag() == "Bullet" && (other->getTag() == "Enemy"))
		_collided = true;
	else if (getTag() == "EnemyBullet" && (other->getTag() == "Player"))
		_collided = true;

	contact->SetEnabled(false);
}

void PiercingBullet::update(const double& deltaTime)
{
	if (!isActive())
		return;

	double dist = _iniPos.distance(_transform->getPosition());

	if (dist < _range && !_collided)
	{
		GameObject::update(deltaTime);

		_body->getBody()->SetLinearVelocity(b2Vec2(_speed * cos(_transform->getRotation() * M_PI / 180.0), _speed * sin(_transform->getRotation() * M_PI / 180.0)));
		_aliveTime++;
	}
	else if (_destroy)
	{
		_destroy = false;
		reset();
	}
}