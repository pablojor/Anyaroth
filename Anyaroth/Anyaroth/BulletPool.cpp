#include "BulletPool.h"
#include "Game.h"


BulletPool::BulletPool(Game* game) : ObjectPool<Bullet, 0>(game)
{

}

Bullet* BulletPool::addNewBullet() 
{
	Bullet* b = new Bullet(getGame());
	_objects.push_back(b);
	b->setWorld(_game->getWorld());
	return b;
}

Bullet * BulletPool::addNewExplosiveBullet()
{
	ExplosiveBullet* b = new ExplosiveBullet(getGame());
	_objects.push_back(b);
	b->setWorld(_game->getWorld());
	return b;
}

void BulletPool::changePoolTag(string tag) {
	for (auto b : _objects)
	{
		b->setTag(tag);
	}
	/*for (int i = 0; i < _objects.size(); i++)
	{
		Bullet* b = getObject(i);
		b->setTag(tag);
	}*/
}

