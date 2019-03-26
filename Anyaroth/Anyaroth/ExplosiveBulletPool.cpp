#include "ExplosiveBulletPool.h"
#include "Game.h"

ExplosiveBulletPool::ExplosiveBulletPool(Game* game) : ObjectPool<ExplosiveBullet, 100>(game) {}

ExplosiveBulletPool::~ExplosiveBulletPool() {}

ExplosiveBullet* ExplosiveBulletPool::addNewBullet()
{
	ExplosiveBullet* b = new ExplosiveBullet(getGame());
	_objects.push_back(b);
	b->setWorld(_game->getWorld());
	return b;
}

void ExplosiveBulletPool::changePoolTag(string tag)
{
	for (auto b : _objects)
		b->setTag(tag);
}