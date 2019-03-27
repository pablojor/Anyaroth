#pragma once
#include "ObjectPool.h"
#include "GravityBullet.h"

class GravityBulletPool :
	public ObjectPool<GravityBullet, 64>
{
public:
	GravityBulletPool(Game* game);
	virtual ~GravityBulletPool();

	Bullet* addNewBullet();
	void changePoolTag(string tag);
};

