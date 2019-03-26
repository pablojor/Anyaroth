#pragma once
#include "ObjectPool.h"
#include "BouncingBullet.h"

class BouncingBulletPool : public ObjectPool<BouncingBullet, 64>
{
public:
	BouncingBulletPool(Game* game);
	virtual ~BouncingBulletPool();

	Bullet* addNewBullet();
	void changePoolTag(string tag);
};

