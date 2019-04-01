#include "BulletEffect.h"
#include "Bullet.h"

BulletEffect::BulletEffect()
{
}


BulletEffect::~BulletEffect()
{
}




void BulletEffect::beginCollision(Bullet* bullet, GameObject * other, b2Contact* contact)
{
	if (bullet->getTag() == "Bullet" && (other->getTag() == "Ground" || other->getTag() == "Enemy"))
		bullet->setCollided(true);
	else if (bullet->getTag() == "EnemyBullet" && (other->getTag() == "Ground" || other->getTag() == "Player"))
		bullet->setCollided(true);

	contact->SetEnabled(false);
}


void BulletEffect::update(Bullet* bullet, double time)
{
	if (bullet->isActive())
	{
		double dist = bullet->getIniPos().distance(bullet->getTransform()->getPosition());

		if (dist < bullet->getRange() && !bullet->hasCollided())
		{
			bullet->GameObject::update(time);

			bullet->getBulletBody()->getBody()->SetLinearVelocity(b2Vec2(bullet->getSpeed() * cos(bullet->getTransform()->getRotation() * M_PI / 180.0), bullet->getSpeed() * sin(bullet->getTransform()->getRotation() * M_PI / 180.0)));
			bullet->setAliveTime(bullet->getAliveTime() + 1);
		}
		else
			reset(bullet);
	}
}


void BulletEffect::reset(Bullet* bullet)
{
	bullet->getBulletBody()->getBody()->SetActive(false);
	bullet->setActive(false);
	bullet->setAliveTime(0);
	bullet->setCollided(false);
}