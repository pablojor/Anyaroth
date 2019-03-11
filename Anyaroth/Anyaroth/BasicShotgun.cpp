#include "BasicShotgun.h"



BasicShotgun::BasicShotgun(Game * game) : Gun(game->getTexture("ArmShotgun"), game->getTexture("PistolBullet"), 100, 25, 60, 2, 30, 800)
{
	_offset = { 28, -1 };
}

BasicShotgun::~BasicShotgun()
{
}

void BasicShotgun::shoot(BulletPool * bulletPool, const Vector2D & position, const double & angle, const string & tag)
{
	if (_clip > 0 && _cadence <= 0)
	{
		_clip--;
		_cadence = _maxCadence;

		for (int i = -1; i < 2; i++)
		{
			//Disparar la bala aqui
			Bullet* b = bulletPool->getUnusedObject();
			Vector2D bulletPos = prepareBulletPosition(position, angle);
			if (b != nullptr)
				b->init(_bulletTexture, bulletPos, _speed, _damage, angle + i * _angleBetweenBullet, _range, tag);
			else
				bulletPool->addNewBullet()->init(_bulletTexture, bulletPos, _speed, _damage, angle + i * _angleBetweenBullet, _range, tag);
		}
	}
}

