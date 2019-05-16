#include "Shotgun.h"
#include "ParticleManager.h"

Shotgun::Shotgun(Game* game, Texture* armTexture, Texture* bulletTexture, string shotSoundTag, double speed, double damage, double range, int maxClip, int maxMagazine, double maxCadence, BulletEffect* effect, GunType id, Texture* iconTexture, bool automatic, BulletAnimType bType) : Gun( game, armTexture,  bulletTexture, shotSoundTag, speed,  damage,  range,  maxClip,  maxMagazine,  maxCadence, effect, id, iconTexture, automatic, bType)
{
	_offset = { 28, -1 };
}

Shotgun::~Shotgun()
{
}

void Shotgun::shoot(BulletPool * bulletPool, const Vector2D & position, double angle, const string & tag)
{
	if (_clip > 0 && _cadence <= 0)
	{
		_clip--;
		_cadence = _maxCadence;

		_game->getSoundManager()->playSFX(_shotSoundTag); //Reproduce el sonido de disparo

		int iniAngleMult = -trunc(double(_numBulletsPerShot) / 2);
		double auxAngle = angle;

		if (_numBulletsPerShot % 2 == 0)	auxAngle = angle + _angleBetweenBullet / 2;

		for (int i = iniAngleMult; i < _numBulletsPerShot + iniAngleMult; i++)
		{
			Bullet* b = bulletPool->getUnusedObject();
			Vector2D bulletPos = prepareBulletPosition(position, angle);

			if (b != nullptr)
				b->init(_bulletTexture, bulletPos, _speed, _damage, auxAngle + i * _angleBetweenBullet, _range, tag, _effect, _bulletAnimType);
			else
				bulletPool->addNewBullet()->init(_bulletTexture, bulletPos, _speed, _damage, auxAngle + i * _angleBetweenBullet, _range, tag, _effect, _bulletAnimType);

			if (createParticles)
			{
				double dir = 0;
				double absAngle = abs(angle);
				Vector2D particlePos = (position + _offset * 0.5).rotateAroundPoint(angle, position);

				if (absAngle > 120)
					dir = -1;

				ParticleManager::GetParticleManager()->CreateSimpleParticle(_bulletTexture, 0.5, particlePos, 15, 135 + 90 * dir, 400, 4);
			}
		}
	}
}

void Shotgun::enemyShoot(BulletPool * bulletPool, const Vector2D & position, double angle, const string & tag)
{
	if (_clip > 0 && _cadence <= 0)
	{
		_cadence = _maxCadence;

		_game->getSoundManager()->playSFX(_shotSoundTag); //Reproduce el sonido de disparo

		int iniAngleMult = -trunc(double(_numBulletsPerShot) / 2);

		double auxAngle = angle;
		if (_numBulletsPerShot % 2 == 0)	auxAngle = angle + _angleBetweenBullet / 2;

		for (int i = iniAngleMult; i < _numBulletsPerShot + iniAngleMult; i++)
		{
			//Disparar la bala aqui
			Bullet* b = bulletPool->getUnusedObject();
			Vector2D bulletPos = prepareBulletPosition(position, angle);
			if (b != nullptr)
			{
				b->init(_bulletTexture, bulletPos, _speed, _damage, auxAngle + i * _angleBetweenBullet, _range, tag, _effect, _bulletAnimType);
				b->changeFilter();
			}
			else
			{
				bulletPool->addNewBullet()->init(_bulletTexture, bulletPos, _speed, _damage, auxAngle + i * _angleBetweenBullet, _range, tag, _effect, _bulletAnimType);
			}
			if (createParticles)
			{
				double dir = 0;
				double absAngle = abs(angle);
				Vector2D particlePos = (position + _offset * 0.5).rotateAroundPoint(angle, position);
				if (absAngle > 120)
				{
					dir = -1;
				}
				ParticleManager::GetParticleManager()->CreateSimpleParticle(_bulletTexture, 0.5, particlePos, 15, 135 + 90 * dir, 400, 4);
			}
		}
	}
}