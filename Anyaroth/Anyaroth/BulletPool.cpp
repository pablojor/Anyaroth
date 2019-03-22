#include "BulletPool.h"
#include "BouncingBullet.h"
#include "Game.h"


BulletPool::BulletPool(Game* game) : ObjectPool<Bullet, 100>(game)
{

}

Bullet* BulletPool::addNewBullet(BulletType type) 
{
	Bullet* b;
	switch (type)
	{
	case Bouncing:
		b = new BouncingBullet(getGame());
		break;
	case Gravity:
		break;
	default:
		b = new Bullet(getGame());
		break;
	}
	_objects.push_back(b);
	return b;
}

void BulletPool::changePoolTag(string tag) {
	for (int i = 0; i < _objects.size(); i++)
	{
		Bullet* b = getObject(i);
		b->setTag(tag);
	}
}

