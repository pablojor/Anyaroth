#include "ExplosiveBulletEffect.h"
#include "Game.h"
#include <math.h>
#include "Bullet.h"

ExplosiveBulletEffect::ExplosiveBulletEffect(int explodeTime) : _explodeTime(explodeTime)
{
}

ExplosiveBulletEffect::~ExplosiveBulletEffect() {}


void ExplosiveBulletEffect::init(Bullet* bullet)
{
	bullet->getBulletBody()->filterCollisions(PLAYER_BULLETS, FLOOR | ENEMIES);
	bullet->getBulletBody()->getBody()->SetType(b2_dynamicBody);
	bullet->getBulletBody()->getBody()->SetBullet(true);
	bullet->getBulletBody()->getBody()->SetFixedRotation(true);
	bullet->getBulletBody()->getBody()->SetGravityScale(6);
	bullet->getBulletBody()->getBody()->SetActive(true);

	bullet->setActive(true);
}

void ExplosiveBulletEffect::beginCollision(Bullet* bullet, GameObject * other, b2Contact * contact)
{
	if (bullet->getTag() == "Bullet" && (other->getTag() == "Ground" || other->getTag() == "Enemy"))
		bullet->setCollided(true);
	else if (bullet->getTag() == "EnemyBullet" && (other->getTag() == "Ground" || other->getTag() == "Player"))
		bullet->setCollided(true);

	contact->SetEnabled(false);
}

void ExplosiveBulletEffect::update(Bullet* bullet, double time)
{
	if (bullet->isActive())
	{

		double dist = bullet->getIniPos().distance(bullet->getTransform()->getPosition());

		if (!bullet->isExploding())
		{
			if (dist < bullet->getRange() && !bullet->hasCollided())
			{
				bullet->GameObject::update(time);
				bullet->setAliveTime(bullet->getAliveTime() + 1);
			}
			else
			{
				explosion(bullet);
				bullet->getBulletBody()->getBody()->SetGravityScale(0);
				bullet->getBulletBody()->getBody()->SetLinearVelocity(b2Vec2_zero);
			}
		}
		else
		{
			if (bullet->getExplosionTime() >= _explodeTime)
			{
				BulletEffect::reset(bullet);
				bullet->setExplosionTime(0);
				bullet->setExploding(false);
				bullet->getBulletBody()->getBody()->DestroyFixture(bullet->getBulletBody()->getBody()->GetFixtureList());
				bullet->getBulletBody()->getBody()->SetGravityScale(4);
			}
			else
				bullet->setExplosionTime(bullet->getExplosionTime() + time);
		}
	}
}

void ExplosiveBulletEffect::explosion(Bullet* bullet)
{
	bullet->setExploding(true);
	b2PolygonShape *explosion=new b2PolygonShape();
	explosion->SetAsBox(bullet->getBulletBody()->getW() * 4, bullet->getBulletBody()->getH() * 4);

	b2FixtureDef* fixt = new b2FixtureDef();
	fixt->restitution = 0;
	fixt->shape = explosion;
	fixt->density = 1;
	fixt->isSensor = true;

	if (bullet->getTag() == "Bullet")
	{
		fixt->filter.categoryBits = PLAYER_BULLETS;
		fixt->filter.maskBits = ENEMIES;
	}
	else
	{
		fixt->filter.categoryBits = ENEMY_BULLETS;
		fixt->filter.maskBits = PLAYER;
	}

	bullet->getBulletBody()->getBody()->CreateFixture(fixt);

	delete fixt;
	delete explosion;
}