#include "BouncingBulletEffect.h"
#include "Bullet.h"


BouncingBulletEffect::BouncingBulletEffect(int maxBounces) : _maxBounces(maxBounces)
{
}


BouncingBulletEffect::~BouncingBulletEffect()
{
}

void BouncingBulletEffect::init(Bullet* bullet)
{
	bullet->getBulletBody()->getBody()->SetGravityScale(0);
	bullet->getBulletBody()->getBody()->GetFixtureList()->SetRestitution(1.0f);
	bullet->getBulletBody()->getBody()->SetLinearVelocity(b2Vec2(bullet->getSpeed() * cos((bullet->getTransform()->getRotation())* M_PI / 180.0), bullet->getSpeed() * sin((bullet->getTransform()->getRotation())* M_PI / 180.0)));
	bullet->getBulletBody()->getBody()->SetLinearDamping(0.0f);
}

void BouncingBulletEffect::beginCollision(Bullet* bullet, GameObject * other, b2Contact* contact)
{
	if (!bullet->isColliding())
	{
		bullet->setIsColliding(true);
		if (bullet->getNumBounces() >= _maxBounces)
		{
			BulletEffect::beginCollision(bullet, other, contact);
		}

		bullet->setNumBounces(bullet->getNumBounces() + 1);
	}
	
}

void BouncingBulletEffect::endCollision(Bullet* bullet, GameObject * other, b2Contact* contact)
{
	bullet->setIsColliding(false);
}

void BouncingBulletEffect::update(Bullet* bullet, double time)
{
	if (bullet->isActive()) {

		double dist = bullet->getIniPos().distance(bullet->getTransform()->getPosition());
		bullet->GameObject::update(time);
		
		if (dist < bullet->getRange() && !bullet->hasCollided() && bullet->getNumBounces() < _maxBounces)
		{

			bullet->setAliveTime(bullet->getAliveTime() + 1);
		}
		else
		{
			if (bullet->getComponent<AnimatedSpriteComponent>()->animationFinished() && bullet->getComponent<AnimatedSpriteComponent>()->getCurrentAnim() == AnimatedSpriteComponent::Destroy)
			{
				reset(bullet);
			}
			else
			{
				bullet->getComponent<BodyComponent>()->getBody()->SetActive(false);
				bullet->getComponent<AnimatedSpriteComponent>()->playAnim(AnimatedSpriteComponent::Destroy);
			}
		}
	}
}

void BouncingBulletEffect::reset(Bullet* bullet)
{
	BulletEffect::reset(bullet);
	bullet->setNumBounces(0);
}
