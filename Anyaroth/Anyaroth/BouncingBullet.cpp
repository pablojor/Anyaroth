#include "BouncingBullet.h"



BouncingBullet::BouncingBullet(Game* game) : Bullet(game)
{
	
}


BouncingBullet::~BouncingBullet()
{
}

void BouncingBullet::beginCollision(GameComponent * other, b2Contact* contact)
{
	if (_numBounces >= _maxBounces)
	{
		if (getTag() == "Bullet" && (other->getTag() == "Suelo" || other->getTag() == "Enemy"))
			_collided = true;
		else if (getTag() == "EnemyBullet" && (other->getTag() == "Suelo" || other->getTag() == "Player"))
			_collided = true;

		contact->SetEnabled(false);
	}
	else
		_transform->setRotation(_transform->getRotation() + _bounceAngle);

	_numBounces++;
	cout << _numBounces << endl;
}

void BouncingBullet::update(double time)
{
	if (isActive()) {

		double dist = _iniPos.distance(_transform->getPosition());

		if (dist < _range && !_collided && _numBounces < 3)
		{
			GameComponent::update(time);


			_body->getBody()->SetLinearVelocity(b2Vec2(_speed * cos((_transform->getRotation())* M_PI / 180.0), _speed * sin((_transform->getRotation())* M_PI / 180.0)));

			_body->getBody()->SetTransform(_body->getBody()->GetPosition(), _transform->getRotation()* M_PI / 180.0);

			_aliveTime++;
		}
		else
			reset();
	}
}

void BouncingBullet::reset()
{
	_body->getBody()->SetActive(false);
	setActive(false);
	_aliveTime = 0;
	_collided = false;
	_numBounces = 0;
}