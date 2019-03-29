#pragma once
#include "ObjectPool.h"
#include "PiercingBullet.h"

class PiercingBulletPool :
	public ObjectPool<PiercingBullet, 64> 
{
public:
	PiercingBulletPool(Game* game);
	virtual ~PiercingBulletPool();

	Bullet* addNewBullet();
	void changePoolTag(string tag);
};

