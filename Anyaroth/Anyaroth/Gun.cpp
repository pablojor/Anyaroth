#include "Gun.h"
#include <algorithm>


Gun::Gun(Texture* armTexture, Texture* bulletTexture, double speed, double damage, double range, int maxClip, int maxMagazine, double maxCadence) : _armTexture(armTexture), _bulletTexture(bulletTexture)
{
	_maxCadence = maxCadence;
	_maxClip = maxClip;
	_maxMagazine = maxMagazine;
	_magazine = _maxMagazine;
	_clip = _maxClip;
	_range = range;
	_damage = damage;
	_speed = speed;
}

void Gun::shoot(BulletPool* bulletPool, const Vector2D& position, const double& angle, const string& tag)
{
	if (_clip > 0 && _cadence <= 0)
	{	
		_clip--;
		_cadence = _maxCadence;

		//Disparar la bala aqui
		Bullet* b = bulletPool->getUnusedObject();
		Vector2D bulletPos = prepareBulletPosition(position, angle);
		if (b != nullptr)
			b->init(_bulletTexture, bulletPos, _speed, _damage, angle, _range, tag);
		else
			bulletPool->addNewBullet()->init(_bulletTexture, bulletPos, _speed, _damage, angle, _range, tag);
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

Vector2D Gun::prepareBulletPosition(const Vector2D & position, const double & angle)
{
	return (position + _offset).rotateAroundPoint(angle, position);
}