#pragma once
#include "ObjectPool.h"
#include "AnimatedSpriteComponent.h"
#include "TransformComponent.h"
#include "MovingComponent.h"
#include "Bullet.h"
#include "Game.h"

class MovingComponent;

template<int SIZE>
class BulletPool : public ObjectPool<Bullet, SIZE>
{
private:
	Texture* _bulletTexture = nullptr;
	double _bulletSpeed = 0, _bulletAngle = 0;
	int _bulletDamage = 0, _bulletRange = 0;

	void initBullets();

public:
	BulletPool(Game* g, Texture* texture, double speed, int damage, int bulletRange) : _bulletTexture(texture), _bulletSpeed(speed), _bulletDamage(damage), _bulletRange(bulletRange), ObjectPool<Bullet, SIZE>(g) { initBullets(); }
	BulletPool(Game* g, Texture* texture, double speed, int damage, double bulletAngle = 0, int bulletRange = 20) : _bulletTexture(texture), _bulletSpeed(speed), _bulletDamage(damage), _bulletAngle(bulletAngle), _bulletRange(bulletRange), ObjectPool<Bullet, SIZE>(g) { initBullets(); }
	virtual ~BulletPool() {}

	void addBullet(Vector2D pos, Vector2D dir, double angle);
	void changePoolTag(string tag);
};

template<int SIZE>
void BulletPool<SIZE>::initBullets()
{
	for (int i = 0; i < SIZE; i++)
	{
		Bullet* b = ObjectPool<Bullet, SIZE>::getObject(i);
		b->init(_bulletTexture, _bulletSpeed, _bulletDamage, _bulletAngle, _bulletRange);
	}
}

template<int SIZE>
void BulletPool<SIZE>::addBullet(Vector2D pos, Vector2D dir, double angle)
{
	Bullet* b = ObjectPool<Bullet,SIZE>::getUnusedObject();

	if (b != nullptr)
	{
		b->reset(pos);

		b->getComponent<TransformComponent>()->setPosition(pos.getX(), pos.getY());
		b->getComponent<TransformComponent>()->setRotation(angle);

		BodyComponent* _body = b->getComponent<BodyComponent>();

		_body->getBody()->SetActive(true);
		_body->getBody()->SetTransform({ (float32)(pos.getX() / 8/*M_TO_PIXEL*/), (float32)(pos.getY() / 8/*M_TO_PIXEL*/) }, _body->getBody()->GetAngle());
		_body->getBody()->SetLinearVelocity({ (float32)(dir.getX() * _bulletSpeed),(float32)(dir.getY() * _bulletSpeed) });

		AnimatedSpriteComponent* _anim = b->getComponent<AnimatedSpriteComponent>();
		_anim->playAnim(AnimatedSpriteComponent::Default);
	}
}

template<int SIZE>
void BulletPool<SIZE>::changePoolTag(string tag)
{
	for (int i = 0; i < SIZE; i++)
	{
		Bullet* b = ObjectPool<Bullet, SIZE>::getObject(i);
		b->setTag(tag);
	}
}