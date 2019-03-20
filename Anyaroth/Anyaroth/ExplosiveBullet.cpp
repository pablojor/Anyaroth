#include "ExplosiveBullet.h"
#include "Game.h"
#include <math.h>

ExplosiveBullet::ExplosiveBullet(Game* game):Bullet(game)
{
	
	_body->filterCollisions(PLAYER_BULLETS, FLOOR | ENEMIES);
	_body->getBody()->SetType(b2_dynamicBody);
	_body->getBody()->SetBullet(true);
	_body->getBody()->SetFixedRotation(true);
	_body->getBody()->SetGravityScale(6);
	_body->getBody()->SetActive(false);


	setActive(false);
}


ExplosiveBullet::~ExplosiveBullet()
{
}

void ExplosiveBullet::beginCollision(GameComponent * other, b2Contact * contact)
{
	if (getTag() == "Bullet" && (other->getTag() == "Suelo" || other->getTag() == "Enemy"))
		_collided = true;
	else if (getTag() == "EnemyBullet" && (other->getTag() == "Suelo" || other->getTag() == "Player"))
		_collided = true;

	contact->SetEnabled(false);
}

void ExplosiveBullet::update(double time)
{
	if (!isActive())
		return;

	double dist = _iniPos.distance(_transform->getPosition());
	if (!_explode)
	{
		if (dist < _range && !_collided)
		{
			GameComponent::update(time);

			//_body->getBody()->SetLinearVelocity(b2Vec2(_speed * cos(_transform->getRotation() * M_PI / 180.0), _speed * sin(_transform->getRotation() * M_PI / 180.0)));
			_aliveTime++;
		}
		else
		{
			explosion();
			_body->getBody()->SetGravityScale(0);
			_body->getBody()->SetLinearVelocity(b2Vec2_zero);
		}
	}
	else
	{
		if (_time >= _explodeTime)
		{
			reset();
			_time = 0;
			_explode = false;
			_body->getBody()->DestroyFixture(_body->getBody()->GetFixtureList());
			_body->getBody()->SetGravityScale(4);
		}
		else
		{
			_time += time;

		}
	}

}

void ExplosiveBullet::explosion()
{
	_explode = true;
	b2PolygonShape *explosion=new b2PolygonShape();
	explosion->SetAsBox(_body->getW() * 4, _body->getH() * 4);

	b2FixtureDef* fixt = new b2FixtureDef();
	fixt->restitution = 0;
	fixt->shape = explosion;
	fixt->density = 1;
	fixt->isSensor = true;
	if (getTag() == "Bullet")
	{
		fixt->filter.categoryBits = PLAYER_BULLETS;
		fixt->filter.maskBits = ENEMIES;
	}
	else
	{
		fixt->filter.categoryBits = ENEMY_BULLETS;
		fixt->filter.maskBits = PLAYER;
	}

	_body->getBody()->CreateFixture(fixt);

	delete fixt;
	delete explosion;
	
}
