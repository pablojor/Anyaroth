#include "PiercingBulletPool.h"
#include "Game.h"


PiercingBulletPool::PiercingBulletPool(Game* game) : ObjectPool<PiercingBullet, 64>(game)
{
}


PiercingBulletPool::~PiercingBulletPool()
{
}


Bullet* PiercingBulletPool::addNewBullet()
{
	PiercingBullet* b = new PiercingBullet(getGame());

	_objects.push_back(b);
	return b;
}

void PiercingBulletPool::changePoolTag(string tag) {
	for (int i = 0; i < _objects.size(); i++)
	{
		PiercingBullet* b = getObject(i);
		b->setTag(tag);
	}
}

