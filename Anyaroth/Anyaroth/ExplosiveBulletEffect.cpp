#include "ExplosiveBulletEffect.h"
#include "Game.h"
#include "Bullet.h"
#include "ParticleManager.h"
#include <math.h>

ExplosiveBulletEffect::ExplosiveBulletEffect(int explodeTime) : _explodeTime(explodeTime)
{
}

ExplosiveBulletEffect::~ExplosiveBulletEffect()
{
}

void ExplosiveBulletEffect::init(Bullet* bullet)
{
	bullet->getBody()->filterCollisions(PLAYER_BULLETS, FLOOR | PLATFORMS | ENEMIES);
	bullet->getBody()->getBody()->SetType(b2_dynamicBody);
	bullet->getBody()->moveShape(b2Vec2(0, bullet->getBody()->getH() + 1));
	bullet->getBody()->getBody()->SetBullet(true);
	bullet->getBody()->getBody()->SetFixedRotation(true);
	bullet->getBody()->getBody()->SetGravityScale(6);
	bullet->getBody()->getBody()->SetActive(true);

	bullet->setActive(true);
}

void ExplosiveBulletEffect::beginCollision(Bullet* bullet, GameObject * other, b2Contact * contact)
{
	if (bullet->getTag() == "Bullet" && (other->getTag() == "Ground" || other->getTag() == "Enemy" || other->getTag() == "Platform" || other->getTag() == "Door"))
		bullet->setCollided(true);
	else if (bullet->getTag() == "EnemyBullet" && (other->getTag() == "Ground" || other->getTag() == "Player" || other->getTag() == "Platform" || other->getTag() == "Door"))
		bullet->setCollided(true);

	contact->SetEnabled(false);
}

void ExplosiveBulletEffect::update(Bullet* bullet, double time)
{
	if (bullet->isActive())
	{
		double dist = bullet->getIniPos().distance(bullet->getTransform()->getPosition());

		bullet->GameObject::update(time);

		if (!bullet->isExploding())
		{
			if (dist < bullet->getRange() && !bullet->hasCollided())
				bullet->setAliveTime(bullet->getAliveTime() + 1);
			else
			{
				explosion(bullet);
				bullet->getComponent<AnimatedSpriteComponent>()->playAnim(AnimatedSpriteComponent::Destroy);
				bullet->getBody()->getBody()->SetGravityScale(0);
				bullet->getBody()->getBody()->SetLinearVelocity(b2Vec2_zero);
			}
		}
		else
		{
			if (bullet->getExplosionTime() >= _explodeTime)
			{
				if (bullet->getComponent<AnimatedSpriteComponent>()->animationFinished() && bullet->getComponent<AnimatedSpriteComponent>()->getCurrentAnim() == AnimatedSpriteComponent::Destroy)
				{
					BulletEffect::reset(bullet);

					bullet->setExplosionTime(0);
					bullet->setExploding(false);
					bullet->getBody()->getBody()->DestroyFixture(bullet->getBody()->getBody()->GetFixtureList());
					bullet->getBody()->getBody()->SetGravityScale(6);
				}
				else
				{
					bullet->getComponent<AnimatedSpriteComponent>()->playAnim(AnimatedSpriteComponent::Destroy);
					bullet->getComponent<BodyComponent>()->getBody()->SetActive(false);
				}
			}
			else
				bullet->setExplosionTime(bullet->getExplosionTime() + time);
		}
	}
}

void ExplosiveBulletEffect::explosion(Bullet* bullet)
{
	bullet->setExploding(true);
	b2PolygonShape *explosion = new b2PolygonShape();
	explosion->SetAsBox(25 / M_TO_PIXEL, 20 / M_TO_PIXEL);

	bullet->getGame()->getCurrentState()->getMainCamera()->shake(3, 500);
	bullet->getGame()->getSoundManager()->playSFX("bombExplosion");

	b2FixtureDef* fixt = new b2FixtureDef();
	fixt->restitution = 0;
	fixt->shape = explosion;
	fixt->density = 1;
	fixt->isSensor = true;

	ParticleManager::GetParticleManager()->CreateExplosion(bullet->getGame()->getTexture("Smoke"), bullet->getTransform()->getPosition(), 20, 40, 400, 15, 2);

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

	bullet->getBody()->getBody()->CreateFixture(fixt);

	delete fixt;
	delete explosion;
}