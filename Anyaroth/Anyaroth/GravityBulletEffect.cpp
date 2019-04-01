#include "GravityBulletEffect.h"
#include "Bullet.h"


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
}

void GravityBulletEffect::beginCollision(Bullet* bullet, GameObject * other, b2Contact* contact)
{
	if (bullet->getTag() == "Bullet" && (other->getTag() == "Ground" || other->getTag() == "Enemy"))
		bullet->setCollided(true);
	else if (bullet->getTag() == "EnemyBullet" && (other->getTag() == "Ground" || other->getTag() == "Player"))
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

				bullet->setAliveTime(bullet->getAliveTime() + 1);
			}
			else
				stop(bullet);
		}
		else if (bullet->getAbsorbingTime() < _maxAbsorbingTime)
		{
			bullet->setAbsorbingTime(bullet->getAbsorbingTime() + 1);;
		}
		else
			reset(bullet);
	}
}

void GravityBulletEffect::reset(Bullet* bullet)
{
	bullet->setAbsorbing(false);
	bullet->setAbsorbingTime(0);
	BulletEffect::reset(bullet);
}

void GravityBulletEffect::stop(Bullet* bullet)
{
	bullet->getBulletBody()->getBody()->SetLinearVelocity(b2Vec2(0,0));
	bullet->setAbsorbing(true);
	bullet->setAbsorbingTime(0);
}
