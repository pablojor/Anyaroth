#pragma once
#include "ObjectPool.h"
#include "Bullet.h"

class BulletPool : public ObjectPool<Bullet, 100>
{
	public:
		BulletPool(Game* game);
		virtual ~BulletPool() {};

		Bullet* addNewBullet();
		void changePoolTag(string tag);
		void stopBullets();
};