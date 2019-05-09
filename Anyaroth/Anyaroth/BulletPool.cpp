#include "BulletPool.h"
#include "Game.h"


BulletPool::BulletPool(Game* game) : ObjectPool<Bullet, 100>(game) {}

Bullet* BulletPool::addNewBullet() 
{
	Bullet* b = new Bullet(getGame());

	_objects.push_back(b);
	b->setWorld(getWorld());
	return b;
}

void BulletPool::changePoolTag(string tag)
{
	for (auto b : _objects)
		b->setTag(tag);
}

void BulletPool::stopBullets()
{
	for (auto b : _objects)
	{
		b->reset();
		b->setActive(false);
	}
}