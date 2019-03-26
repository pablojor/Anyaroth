#include "BouncingBulletPool.h"
#include "Game.h"


BouncingBulletPool::BouncingBulletPool(Game* game) : ObjectPool<BouncingBullet, 64>(game)
{
}


BouncingBulletPool::~BouncingBulletPool()
{
}


Bullet* BouncingBulletPool::addNewBullet()
{
	BouncingBullet* b = new BouncingBullet(getGame());

	_objects.push_back(b);
	return b;
}

void BouncingBulletPool::changePoolTag(string tag) {
	for (int i = 0; i < _objects.size(); i++)
	{
		BouncingBullet* b = getObject(i);
		b->setTag(tag);
	}
}

