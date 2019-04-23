#include "BouncingBullet.h"

BouncingBullet::BouncingBullet(Game* game) : Bullet(game)
{
	_body->getBody()->SetLinearDamping(1.0f);
	_body->getBody()->GetFixtureList()->SetRestitution(1.0f);
}

BouncingBullet::~BouncingBullet()
{
}

void BouncingBullet::beginCollision(GameObject * other, b2Contact* contact)
{
	if (!_isColliding)
	{
		_isColliding = true;
		if (_numBounces >= _maxBounces)
		{
			Bullet::beginCollision(other, contact);
		}
		/*else
		_transform->setRotation(_transform->getRotation() + _bounceAngle);*/

		_numBounces++;
		cout << _numBounces << endl;
	}
}

void BouncingBullet::endCollision(GameObject * other, b2Contact* contact)
{
	_isColliding = false;
}

void BouncingBullet::update(double deltaTime)
{
	if (isActive()) {

		double dist = _iniPos.distance(_transform->getPosition());
		GameObject::update(time);

		if (dist < _range && !_collided && _numBounces < _maxBounces)
		{
			_aliveTime++;
		}
		else
		{
			if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::Destroy)
			{
				reset();
			}
			else
			{
				_body->getBody()->SetActive(false);
				_anim->playAnim(AnimatedSpriteComponent::Destroy);
			}
		}
	}
}

void BouncingBullet::reset()
{
	Bullet::reset();
	_numBounces = 0;
}

void BouncingBullet::init(Texture* texture, const Vector2D& position, const double& speed, const double& damage, const double& angle, const double& range, const string& tag, string type)
{
	Bullet::init(texture, position, speed, damage, angle, range, tag, type);
	_body->getBody()->SetLinearVelocity(b2Vec2(_speed * cos((_transform->getRotation())* M_PI / 180.0), _speed * sin((_transform->getRotation())* M_PI / 180.0)));
	_body->getBody()->SetLinearDamping(0.0f);
}