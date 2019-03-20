#pragma once
#include "ObjectPool.h"
#include "Bullet.h"
#include "ExplosiveBullet.h"

class BulletPool : public ObjectPool<Bullet, 0>
{
	private:
		void initBullets();

	public:
		BulletPool(Game* game);
		virtual ~BulletPool() {};

		Bullet* addNewBullet();
		Bullet* addNewExplosiveBullet();
		void changePoolTag(string tag);
};