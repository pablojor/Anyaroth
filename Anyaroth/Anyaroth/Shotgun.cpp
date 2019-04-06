#include "Shotgun.h"



Shotgun::Shotgun(Texture* armTexture, Texture* bulletTexture, double speed, double damage, double range, int maxClip, int maxMagazine, double maxCadence, bool automatic, GunType id) : Gun( armTexture,  bulletTexture,  speed,  damage,  range,  maxClip,  maxMagazine,  maxCadence,  automatic, id)
{
	_offset = { 28, -1 };
}


Shotgun::~Shotgun()
{
}


void Shotgun::shoot(BulletPool * bulletPool, const Vector2D & position, const double & angle, const string & tag)
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
				b->init(_bulletTexture, bulletPos, _speed, _damage, angle + i * _angleBetweenBullet, _range, tag);
			else
				bulletPool->addNewBullet()->init(_bulletTexture, bulletPos, _speed, _damage, angle + i * _angleBetweenBullet, _range, tag);
		}
	}
}