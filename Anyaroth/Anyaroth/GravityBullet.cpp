#include "GravityBullet.h"



GravityBullet::GravityBullet(Game* game) : Bullet(game)
{
}


GravityBullet::~GravityBullet()
{
}



void GravityBullet::beginCollision(GameComponent * other, b2Contact* contact)
{
	if (getTag() == "Bullet" && (other->getTag() == "Ground" || other->getTag() == "Enemy"))
		_collided = true;
	else if (getTag() == "EnemyBullet" && (other->getTag() == "Ground" || other->getTag() == "Player"))
		_collided = true;

	contact->SetEnabled(false);
}

void GravityBullet::init(Texture* texture, const Vector2D& position, const double& speed, const double& damage, const double& angle, const double& range, const string& tag)
{
	Bullet::init(texture, position, speed, damage, angle, range, tag);
	_body->getBody()->SetLinearVelocity(b2Vec2(_speed * cos((_transform->getRotation())* M_PI / 180.0), _speed * sin((_transform->getRotation())* M_PI / 180.0)));
	_body->getBody()->SetLinearDamping(0.0f);
}

void GravityBullet::update(double time)
{
	if (isActive())
	{
		if (!_absorbing)
		{
			double dist = _iniPos.distance(_transform->getPosition());

			if (dist < _range && !_collided)
			{
				GameComponent::update(time);

				_aliveTime++;
			}
			else
				stop();
		}
		else if (_absorbingTime < _maxAbsorbingTime)
		{
			_absorbingTime++;
		}
		else
			reset();
	}
}

void GravityBullet::reset()
{
	_absorbing = false;
	_absorbingTime = 0;
	Bullet::reset();
}

void GravityBullet::stop()
{
	_body->getBody()->SetLinearVelocity(b2Vec2(0,0));
	_absorbing = true;
	_absorbingTime = 0;
}
