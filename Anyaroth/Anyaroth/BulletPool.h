#pragma once
#include "ObjectPool.h"
#include "Bullet.h"

enum BulletType
{
	Normal,
	Bouncing,
	Gravity
};

class BulletPool : public ObjectPool<Bullet, 100>
{
	private:
		void initBullets();

	public:
		BulletPool(Game* game);
		virtual ~BulletPool() {};

		Bullet* addNewBullet(BulletType type = Normal);
		void changePoolTag(string tag);
};