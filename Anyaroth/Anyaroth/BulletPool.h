#pragma once
#include "ObjectPool.h"
#include "Bullet.h"

template<int SIZE>
class BulletPool :
	public ObjectPool<Bullet, SIZE>
{
private:
	Texture* _bulletTexture = nullptr;
	double _bulletSpeed = 0;
	int _bulletDamage = 0;
public:
	BulletPool(Texture* texture, double speed, int damage) : _bulletTexture(texture), _bulletSpeed(speed), _bulletDamage(damage) {};
	virtual ~BulletPool() {};

	void addBullet(Vector2D pos, Vector2D dir);
};




template<int SIZE>
void BulletPool<SIZE>::addBullet(Vector2D pos, Vector2D dir) {
	Bullet* b = ObjectPool::getUnusedObject();
	if (b != nullptr) {
		b->getComponent<AnimatedSpriteComponent>()->setTexture(_bulletTexture);
		b->setSpeed(_bulletSpeed);
		b->setDamage(_bulletDamage);
		b->getComponent<TransformComponent>()->setPosition(pos);
		b->getComponent<MovingComponent>()->changeDir(dir.getX(),dir.getY());
	}
}