#include "Shotgun.h"



Shotgun::Shotgun(Texture* armTexture, Texture* bulletTexture, double speed, double damage, double range, int maxClip, int maxMagazine, double maxCadence, BulletEffect* effect, GunType id, bool automatic, BulletAnimType bType, Texture* iconTexture) : Gun( armTexture,  bulletTexture,  speed,  damage,  range,  maxClip,  maxMagazine,  maxCadence, effect, id, automatic, bType, iconTexture)
{
	_offset = { 28, -1 };
}


Shotgun::~Shotgun()
{
}


void Shotgun::shoot(PoolWrapper * bulletPool, const Vector2D & position, const double & angle, const string & tag)
{
	if (_clip > 0 && _cadence <= 0)
	{
		_clip--;
		_cadence = _maxCadence;

		int iniAngleMult = -trunc(double(_numBulletsPerShot) / 2);

		for (int i = iniAngleMult; i < _numBulletsPerShot + iniAngleMult; i++)
		{
			//Disparar la bala aqui
			Bullet* b = bulletPool->getUnusedObject();
			Vector2D bulletPos = prepareBulletPosition(position, angle);
			if (b != nullptr)
				b->init(_bulletTexture, bulletPos, _speed, _damage, angle + i * _angleBetweenBullet, _range, tag, _effect, _bulletAnimType);
			else
				bulletPool->addNewBullet()->init(_bulletTexture, bulletPos, _speed, _damage, angle + i * _angleBetweenBullet, _range, tag, _effect, _bulletAnimType);
		}
	}
}