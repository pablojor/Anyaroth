#include "GravityBulletEffect.h"
#include "Bullet.h"
#include "Game.h"
#include "SpriteObject.h"

GravityBulletEffect::GravityBulletEffect(int maxAbsorbTime) : _maxAbsorbingTime(maxAbsorbTime)
{
}

GravityBulletEffect::~GravityBulletEffect()
{
	_debuffs.clear();
}

void GravityBulletEffect::init(Bullet* bullet)
{
	bullet->getBody()->getBody()->SetLinearVelocity(b2Vec2(bullet->getSpeed() * cos((bullet->getTransform()->getRotation())* M_PI / 180.0), bullet->getSpeed() * sin((bullet->getTransform()->getRotation())* M_PI / 180.0)));
	bullet->getBody()->getBody()->SetLinearDamping(0.0f);

	_auxTag = bullet->getTag();
	bullet->setTag("GravityBullet");
}

void GravityBulletEffect::beginCollision(Bullet* bullet, GameObject * other, b2Contact* contact)
{
	if (other->getTag() == "Ground" || other->getTag() == "Platform" || other->getTag() == "Door")
		bullet->setCollided(true);
	else if(other->getTag() == "Enemy" || other->getTag() == "Player")
	{
		bullet->setCollided(true);
		other->setStunned(true);

		GravityBombDebuff* gd = other->getComponent<GravityBombDebuff>();

		if (gd == nullptr)
			gd = new GravityBombDebuff(other, bullet);
		else
			gd->setZone(bullet);

		_debuffs.push_back(gd);
		gd->absorb();
	}

	contact->SetEnabled(false);
}

void GravityBulletEffect::update(Bullet* bullet, double time)
{
	if (bullet->isActive())
	{
		bullet->GameObject::update(time);

		if (!bullet->isAbsorbing())
		{
			double dist = bullet->getIniPos().distance(bullet->getTransform()->getPosition());

			if (dist < bullet->getRange() && !bullet->hasCollided())
				bullet->setAliveTime(bullet->getAliveTime() + time);
			else
			{
				startAbsorbing(bullet);
				bullet->getComponent<AnimatedSpriteComponent>()->playAnim(AnimatedSpriteComponent::Destroy);

				SpriteObject* sprite = new SpriteObject(bullet->getGame(), bullet->getGame()->getTexture("BHArea"),
					{ bullet->getComponent<TransformComponent>()->getPosition().getX() - 115,
					bullet->getComponent<TransformComponent>()->getPosition().getY() - 95 });

				bullet->addChild(sprite);
			}
		}
		else if (bullet->getAbsorbingTime() < _maxAbsorbingTime)
			bullet->setAbsorbingTime(bullet->getAbsorbingTime() + time);
		else
			reset(bullet);
	}
}

void GravityBulletEffect::reset(Bullet* bullet)
{
	bullet->setAbsorbing(false);
	bullet->setAbsorbingTime(0);
	bullet->getBody()->getBody()->SetType(b2_dynamicBody);
	bullet->getBody()->getBody()->DestroyFixture(bullet->getBody()->getBody()->GetFixtureList());

	//Termina el debuff de los enemigos afectados
	for (GravityBombDebuff* gd : _debuffs)
		gd->stop();
	_debuffs.clear();

	bullet->destroyAllChildren(); //borra el sprite de área

	bullet->getGame()->getSoundManager()->removeSFX("duringBH");
	bullet->getGame()->getSoundManager()->addSFX("duringBH", SOUNDS_PATH + "duringBH.wav");
	
	BulletEffect::reset(bullet);
}

void GravityBulletEffect::startAbsorbing(Bullet* bullet)
{
	bullet->getBody()->getBody()->SetLinearVelocity(b2Vec2(0,0));
	bullet->setAbsorbing(true);
	bullet->setAbsorbingTime(0);
	bullet->getBody()->getBody()->SetLinearVelocity(b2Vec2(b2Vec2_zero));
	bullet->getBody()->getBody()->SetType(b2_staticBody);

	bullet->setTag(_auxTag);

	b2PolygonShape *explosion = new b2PolygonShape();
	explosion->SetAsBox(_absorbingRange, _absorbingRange);

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

	bullet->getGame()->getSoundManager()->playSFX("duringBH");

	bullet->getBody()->getBody()->CreateFixture(fixt);

	delete fixt;
	delete explosion;
}