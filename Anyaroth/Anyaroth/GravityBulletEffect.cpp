#include "GravityBulletEffect.h"
#include "Bullet.h"
#include "Game.h"
#include "MovingComponent.h"
#include "SpriteObject.h"


GravityBulletEffect::GravityBulletEffect(int maxAbsorbTime) : _maxAbsorbingTime(maxAbsorbTime)
{
}


GravityBulletEffect::~GravityBulletEffect()
{
	/*for (GravityBombDebuff* gd : _debuffs)
	{
		if (gd != nullptr) { delete gd; gd = nullptr; }
	}*/

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
	if (/*bullet->getTag() == "GravityBullet" && */other->getTag() == "Ground" || other->getTag()
		== "Platform")
	{
		bullet->setCollided(true);

	}
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


		/*auto body = other->getComponent<BodyComponent>()->getBody();
		Vector2D vectorToGravZone = { (bullet->getComponent<TransformComponent>()->getPosition().getX() - other->getComponent<TransformComponent>()->getPosition().getX())*M_TO_PIXEL, (bullet->getComponent<TransformComponent>()->getPosition().getY() - other->getComponent<TransformComponent>()->getPosition().getY())*M_TO_PIXEL };
		//vectorToGravZone.normalize();

		//body->ApplyLinearImpulseToCenter(b2Vec2(vectorToGravZone.getX() * 2000, vectorToGravZone.getY() * 2000), true);
		body->SetLinearVelocity(b2Vec2(vectorToGravZone.getX() * 2000, vectorToGravZone.getY() * 2000));*/
	}


	//else if (/*bullet->getTag() == "GravityBullet" && */(other->getTag() == "Ground" || other->getTag() == "Player"))
		//bullet->setCollided(true);

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
			{
				

				bullet->setAliveTime(bullet->getAliveTime() + time);
			}
			else
			{
				startAbsorbing(bullet);
				bullet->getComponent<AnimatedSpriteComponent>()->playAnim(AnimatedSpriteComponent::Destroy);

				SpriteObject* sprite = new SpriteObject(bullet->getGame(), bullet->getGame()->getTexture("Mk"), bullet->getComponent<TransformComponent>()->getPosition());
				//sprite->getComponent<TransformComponent>()->setScale(40);
				bullet->addChild(sprite);
			}
		}
		else if (bullet->getAbsorbingTime() < _maxAbsorbingTime)
		{
			bullet->setAbsorbingTime(bullet->getAbsorbingTime() + time);
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

	//Termina el debuffo de los enemigos afectados
	for (GravityBombDebuff* gd : _debuffs)
	{
		gd->stop();
	}
	_debuffs.clear();

	bullet->destroyAllChildren(); //borra el sprite de área
	
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

	bullet->getBulletBody()->getBody()->CreateFixture(fixt);

	delete fixt;
	delete explosion;
}
