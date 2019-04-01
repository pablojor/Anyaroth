#include "GravityBulletEffect.h"
#include "Bullet.h"
#include "Game.h"


GravityBulletEffect::GravityBulletEffect(int maxAbsorbTime) : _maxAbsorbingTime(maxAbsorbTime)
{
}


GravityBulletEffect::~GravityBulletEffect()
{
}



void GravityBulletEffect::init(Bullet* bullet)
{
	//	Bullet::init(texture, position, speed, damage, angle, range, tag);
	bullet->getBulletBody()->getBody()->SetLinearVelocity(b2Vec2(bullet->getSpeed() * cos((bullet->getTransform()->getRotation())* M_PI / 180.0), bullet->getSpeed() * sin((bullet->getTransform()->getRotation())* M_PI / 180.0)));
	bullet->getBulletBody()->getBody()->SetLinearDamping(0.0f);

	_auxTag = bullet->getTag();
	bullet->setTag("GravityBullet");
	
}

void GravityBulletEffect::beginCollision(Bullet* bullet, GameObject * other, b2Contact* contact)
{
	if (/*bullet->getTag() == "GravityBullet" && */(other->getTag() == "Ground" || other->getTag() == "Enemy"))
		bullet->setCollided(true);
	else if (/*bullet->getTag() == "GravityBullet" && */(other->getTag() == "Ground" || other->getTag() == "Player"))
		bullet->setCollided(true);

	contact->SetEnabled(false);
}

void GravityBulletEffect::update(Bullet* bullet, double time)
{
	if (bullet->isActive())
	{
		if (!bullet->isAbsorbing())
		{
			double dist = bullet->getIniPos().distance(bullet->getTransform()->getPosition());

			if (dist < bullet->getRange() && !bullet->hasCollided())
			{
				bullet->GameObject::update(time);

				bullet->setAliveTime(bullet->getAliveTime() + time);
			}
			else
				startAbsorbing(bullet);
		}
		else if (bullet->getAbsorbingTime() < _maxAbsorbingTime)
		{
			bullet->setAbsorbingTime(bullet->getAbsorbingTime() + time);;
		}
		else
			reset(bullet);
	}
}

void GravityBulletEffect::reset(Bullet* bullet)
{
	bullet->setAbsorbing(false);
	bullet->setAbsorbingTime(0);
	bullet->getBulletBody()->getBody()->SetType(b2_dynamicBody);
	bullet->getBulletBody()->getBody()->DestroyFixture(bullet->getBulletBody()->getBody()->GetFixtureList());
	BulletEffect::reset(bullet);
}

void GravityBulletEffect::startAbsorbing(Bullet* bullet)
{
	bullet->getBulletBody()->getBody()->SetLinearVelocity(b2Vec2(0,0));
	bullet->setAbsorbing(true);
	bullet->setAbsorbingTime(0);
	bullet->getBulletBody()->getBody()->SetLinearVelocity(b2Vec2(b2Vec2_zero));
	bullet->getBulletBody()->getBody()->SetType(b2_staticBody);

	bullet->setTag(_auxTag);

	b2PolygonShape *explosion = new b2PolygonShape();
	explosion->SetAsBox(bullet->getBulletBody()->getW() * _absorbingRange, bullet->getBulletBody()->getH() * _absorbingRange);

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
