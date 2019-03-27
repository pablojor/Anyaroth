#include "GravityBulletPool.h"
#include "Game.h"


GravityBulletPool::GravityBulletPool(Game* game) : ObjectPool<GravityBullet, 64>(game)
{
}


GravityBulletPool::~GravityBulletPool()
{
}


Bullet* GravityBulletPool::addNewBullet()
{
	GravityBullet* b = new GravityBullet(getGame());

	_objects.push_back(b);
	return b;
}

void GravityBulletPool::changePoolTag(string tag) {
	for (int i = 0; i < _objects.size(); i++)
	{
		GravityBullet* b = getObject(i);
		b->setTag(tag);
	}
}

