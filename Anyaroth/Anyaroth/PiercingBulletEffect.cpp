#include "PiercingBulletEffect.h"
#include "Bullet.h"


PiercingBulletEffect::PiercingBulletEffect()
{
}


PiercingBulletEffect::~PiercingBulletEffect()
{
}


void PiercingBulletEffect::init(Bullet* bullet)
{
	bullet->getBulletBody()->getBody()->GetFixtureList()->SetSensor(true);
}

void PiercingBulletEffect::beginCollision(Bullet* bullet, GameObject * other, b2Contact* contact)
{
	if (other->getTag() == "Ground")
		bullet->setCollided(true);	//_destroy = true;
	/*else if (getTag() == "Bullet" && (other->getTag() == "Enemy"))
		_collided = true;
	else if (getTag() == "EnemyBullet" && (other->getTag() == "Player"))
		_collided = true;*/

	contact->SetEnabled(false);
}

void PiercingBulletEffect::update(Bullet* bullet, double time)
{
	if (bullet->isActive())
	{
		double dist = bullet->getIniPos().distance(bullet->getTransform()->getPosition());

		if (bullet->hasCollided())
		{
			bullet->setCollided(false);
			BulletEffect::reset(bullet);
		}
		else if (dist < bullet->getRange())
		{
			bullet->GameObject::update(time);

			bullet->getBulletBody()->getBody()->SetLinearVelocity(b2Vec2(bullet->getSpeed() * cos(bullet->getTransform()->getRotation() * M_PI / 180.0), bullet->getSpeed() * sin(bullet->getTransform()->getRotation() * M_PI / 180.0)));
			bullet->setAliveTime(bullet->getAliveTime() + 1);
		}
		
	}
}