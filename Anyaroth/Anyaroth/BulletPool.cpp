#include "BulletPool.h"
#include "Game.h"


BulletPool::BulletPool(Game* game) : ObjectPool<Bullet, 100>(game)
{

}

Bullet* BulletPool::addNewBullet() 
{
	Bullet* b = new Bullet(getGame());
	_objects.push_back(b);
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

