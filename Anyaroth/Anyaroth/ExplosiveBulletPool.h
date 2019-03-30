/*#pragma once
#include "ObjectPool.h"
#include "ExplosiveBullet.h"

class ExplosiveBulletPool : public ObjectPool<ExplosiveBulletEffect, 100>
{
public:
	ExplosiveBulletPool(Game* game);
	virtual ~ExplosiveBulletPool();

	ExplosiveBulletEffect* addNewBullet();
	void changePoolTag(string tag);
};*/