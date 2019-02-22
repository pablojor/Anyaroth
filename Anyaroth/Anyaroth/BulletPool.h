#pragma once
#include "ObjectPool.h"
#include "AnimatedSpriteComponent.h"
#include "TransformComponent.h"
#include "MovingComponent.h"
#include "Bullet.h"

class MovingComponent;

template<int SIZE>
class BulletPool :
	public ObjectPool<Bullet, SIZE>
{
private:
	Texture* _bulletTexture = nullptr;
	double _bulletSpeed = 0;
	int _bulletDamage = 0;
	int _bulletRange = 20;


	void initBullets();
public:
	BulletPool(Game* g, Texture* texture, double speed, int damage, int bulletRange = 20) : _bulletTexture(texture), _bulletSpeed(speed), _bulletDamage(damage), _bulletRange(bulletRange), ObjectPool<Bullet, SIZE>(g) { initBullets(); };
	virtual ~BulletPool() {};


	void addBullet(Vector2D pos, Vector2D dir);
};



template<int SIZE>
void BulletPool<SIZE>::initBullets() {
	for (int i = 0; i < SIZE; i++)
	{
		Bullet* b = ObjectPool<Bullet, SIZE>::getObject(i);
		b->init(_bulletTexture, _bulletSpeed, _bulletDamage);
		b->getComponent<AnimatedSpriteComponent>()->setTexture(_bulletTexture);
	}
}


template<int SIZE>
void BulletPool<SIZE>::addBullet(Vector2D pos, Vector2D dir) {
	Bullet* b = ObjectPool<Bullet,SIZE>::getUnusedObject();

	if (b != nullptr) {
			
		
		b->getComponent<TransformComponent>()->setPosition(pos.getX(), pos.getY());
		//b->getComponent<MovingComponent>()->changeDir(dir.getX(),dir.getY());
		b->reset();
	}
}