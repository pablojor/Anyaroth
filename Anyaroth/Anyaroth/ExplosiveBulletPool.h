#pragma once
#include "ObjectPool.h"
#include "ExplosiveBullet.h"

class ExplosiveBulletPool : public ObjectPool<ExplosiveBullet, 100>
{
public:
	ExplosiveBulletPool(Game* game);
	virtual ~ExplosiveBulletPool();

	ExplosiveBullet* addNewBullet();
	void changePoolTag(string tag);
};