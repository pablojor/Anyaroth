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
	if (bullet->getTag() == "Bullet" && (other->getTag() == "Ground" || other->getTag() == "Enemy" || other->getTag() == "Platform" || other->getTag() == "Door"))
		bullet->setCollided(true);
	else if (bullet->getTag() == "EnemyBullet" && (other->getTag() == "Ground" || other->getTag() == "Player" || other->getTag() == "Platform" || other->getTag() == "Door"))
		bullet->setCollided(true);

	contact->SetEnabled(false);
}

void BulletEffect::update(Bullet* bullet, double time)
{
	if (bullet->isActive())
	{
		double dist = bullet->getIniPos().distance(bullet->getTransform()->getPosition());

		bullet->GameObject::update(time);

		if (dist < bullet->getRange() && !bullet->hasCollided())
		{
			bullet->getBody()->getBody()->SetLinearVelocity(b2Vec2(bullet->getSpeed() * cos(bullet->getTransform()->getRotation() * M_PI / 180.0), bullet->getSpeed() * sin(bullet->getTransform()->getRotation() * M_PI / 180.0)));
			bullet->setAliveTime(bullet->getAliveTime() + 1);
		}
		else
		{
			if ((bullet->getComponent<AnimatedSpriteComponent>()->animationFinished() && bullet->getComponent<AnimatedSpriteComponent>()->getCurrentAnim() == AnimatedSpriteComponent::Destroy))
				reset(bullet);
			else
			{
				bullet->getComponent<BodyComponent>()->getBody()->SetActive(false);
				bullet->getComponent<AnimatedSpriteComponent>()->playAnim(AnimatedSpriteComponent::Destroy);
			}
		}
	}
}

void BulletEffect::reset(Bullet* bullet)
{
	bullet->getComponent<AnimatedSpriteComponent>()->playAnim(AnimatedSpriteComponent::Default);
	bullet->setActive(false);
	bullet->setAliveTime(0);
	bullet->setCollided(false);
	bullet->getComponent<AnimatedSpriteComponent>()->reset();
	bullet->getComponent<BodyComponent>()->getBody()->SetActive(false);
}