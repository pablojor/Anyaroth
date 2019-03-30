/*#include "ExplosiveBulletPool.h"
#include "Game.h"

ExplosiveBulletPool::ExplosiveBulletPool(Game* game) : ObjectPool<ExplosiveBulletEffect, 100>(game) {}

ExplosiveBulletPool::~ExplosiveBulletPool() {}

ExplosiveBulletEffect* ExplosiveBulletPool::addNewBullet()
{
	ExplosiveBulletEffect* b = new ExplosiveBulletEffect(getGame());
	_objects.push_back(b);
	b->setWorld(_game->getWorld());
	return b;
}

void ExplosiveBulletPool::changePoolTag(string tag)
{
	for (auto b : _objects)
		b->setTag(tag);
}*/