#include "Gun.h"
#include <algorithm>


Gun::Gun(Texture* texture, int maxClip, int maxMagazine) : _armTexture(texture)
{
	_maxClip = maxClip;
	_maxMagazine = maxMagazine;
	_magazine = _maxMagazine;
	_clip = _maxClip;
}

void Gun::shoot()
{
	if (_clip > 0 && _cadence <= 0)
	{	
		_clip--;
		_cadence = _maxCadence;
		//Disparar la bala aqui

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
// USAR ESTE METODO AL RECOGER MUNICION
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