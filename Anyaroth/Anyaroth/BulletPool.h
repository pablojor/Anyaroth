#pragma once
#include "ObjectPool.h"
#include "Bullet.h"


class BulletPool : public ObjectPool<Bullet, 100>
{
	private:
		/*Texture* _bulletTexture = nullptr;
		double _bulletSpeed = 0;
		int _bulletDamage = 0;
		int _bulletRange = 0;
		double _bulletAngle = 0;*/

		void initBullets();

	public:
		BulletPool(Game* game);
		virtual ~BulletPool() {};

		Bullet* addNewBullet();
		void changePoolTag(string tag);
};
