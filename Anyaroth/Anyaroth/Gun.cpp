#include "Gun.h"
#include "ParticleManager.h"
#include <algorithm>

Gun::Gun(Game* game, Texture* armTexture, Texture* bulletTexture, string shotSoundTag, double speed, double damage, double range, int maxClip, int maxMagazine, int maxCadence, EffectInterface* effect, GunType id, Texture* iconTexture, bool automatic, BulletAnimType bType) : _armTexture(armTexture), _bulletTexture(bulletTexture), _shotSoundTag(shotSoundTag), _iconTexture(iconTexture)
{
	_game = game;
	_maxCadence = maxCadence;
	_maxClip = maxClip;
	_maxMagazine = maxMagazine;
	_magazine = _maxMagazine;
	_clip = _maxClip;
	_range = range;
	_damage = damage;
	_speed = speed;
	_isAutomatic = automatic;
	_id = id;
	_effect = effect;
	_bulletAnimType = bType;
}

void Gun::shoot(BulletPool* bulletPool, const Vector2D& position, double angle, const string& tag)
{
	if (_clip > 0 && _cadence <= 0)
	{	
		_clip--;
		_cadence = _maxCadence;

		_game->getSoundManager()->playSFX(_shotSoundTag, _id); //Reproduce el sonido de disparo


		//Disparar la bala aqui
		Bullet* b = bulletPool->getUnusedObject();
		Vector2D bulletPos = prepareBulletPosition(position, angle);
		
		if (b != nullptr)
			b->init(_bulletTexture, bulletPos, _speed, _damage, angle, _range, tag, _effect, _bulletAnimType);
		else
			bulletPool->addNewBullet()->init(_bulletTexture, bulletPos, _speed, _damage, angle, _range, tag, _effect, _bulletAnimType);

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

void Gun::enemyShoot(BulletPool* bulletPool, const Vector2D& position, double angle, const string& tag)
{
	if (_cadence <= 0)
	{
		_cadence = _maxCadence;

		_game->getSoundManager()->playSFX(_shotSoundTag, _id); //Reproduce el sonido de disparo

		//Disparar la bala aqui
		Bullet* b = bulletPool->getUnusedObject();
		Vector2D bulletPos = prepareBulletPosition(position, angle);
		if (b != nullptr)
		{
			b->init(_bulletTexture, bulletPos, _speed, _damage, angle, _range, tag, _effect, _bulletAnimType);
			b->changeFilter();
		}
		else
		{
			Bullet* b2 = bulletPool->addNewBullet();
			b2->init(_bulletTexture, bulletPos, _speed, _damage, angle, _range, tag, _effect, _bulletAnimType);
			b2->changeFilter();
		}
	}
}

void Gun::reload()
{
	if (_clip < _maxClip)
	{
		int diff = _maxClip - _clip;
		if (diff <= _magazine)
		{
			_clip = _maxClip;
			_magazine -= diff;
		}
		else
		{
			_clip += _magazine;
			_magazine = 0;
		}
		_cadence = 0;
	}
}

// Suma ammoAdded a la municion y la coloca en _ammo y _clip segun corresponda
void Gun::addAmmo(int ammoAdded)
{
	if (_magazine + ammoAdded > _maxMagazine) //Si sobran balas en _ammo
	{
		int prevAmmo = _magazine;
		_magazine = _maxMagazine;

		//Suma las balas sobrantes al cargador hasta llenarlo
		int leftAmmo = ammoAdded - (_magazine - prevAmmo);
		_clip = min(_maxClip, _clip + (_magazine - leftAmmo));
	}
	else
		_magazine += ammoAdded;
}

//Pone al maximo la municion tanto en _ammo como en el cargador _clip
void Gun::resetAmmo()
{
	_magazine = _maxMagazine;
	_clip = _maxClip;
}

void Gun::clearAmmo()
{
	_magazine = 0;
	_clip = 0;
}

Vector2D Gun::prepareBulletPosition(const Vector2D & position, double angle)
{
	return (position + _offset).rotateAroundPoint(angle, position);
}