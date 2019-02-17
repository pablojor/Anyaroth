#include "Gun.h"
#include "AnimatedSpriteComponent.h"
#include <algorithm>


Gun::Gun(GameComponent* shootingObj, Shooter* shooterComp, string name, int maxAmmo, int maxClip, int bulletsPerShot) : _shootingObj(shootingObj), _shooterComp(shooterComp), _name(name), _maxAmmo(maxAmmo), _maxClip(maxClip), _ammo(maxAmmo), _clip(maxClip), _bulletsPerShot(bulletsPerShot)
{

}


Gun::~Gun()
{

}


//método auxiliar de reload
void Gun::reloadAux(int newClipValue)
{
	int prevClip = _clip; //cargador antes de recargar
	_clip = newClipValue;
	_ammo -= (_clip - prevClip); //resta a la munición total la munición recargada
}

//Recarga la munición si puede y devuelve true si ha recargado
bool Gun::reload()
{
	if (_clip < _maxClip) { //Si el cargador no está completo
		//llamo a animación de recargar



		if (_ammo >= _maxClip)
			reloadAux(_maxClip);
		else if (_ammo > 0) reloadAux(min(_maxClip, _clip + _ammo));
		else return false;

		cout << "Recargando! Cubranme!" << endl;
		cout << "Ammo: " << _ammo << "/" << _maxAmmo << endl;
		cout << "Clip: " << _clip << "/" << _maxClip << endl;

		return true;
	}
	else
		return false;
}

// Suma ammoAdded a la munición y la coloca en _ammo y _clip según corresponda
// USAR ESTE MÉTODO AL RECOGER MUNICIÓN
void Gun::addAmmo(int ammoAdded)
{
	if (_ammo + ammoAdded > _maxAmmo) //Si sobran balas en _ammo
	{
		int prevAmmo = _ammo;
		_ammo = _maxAmmo;

		//Suma las balas sobrantes al cargador hasta llenarlo
		int leftAmmo = ammoAdded - (_ammo - prevAmmo);
		_clip = min(_maxClip, _clip + (_ammo - leftAmmo));
	}
	else
	{
		_ammo += ammoAdded;
	}
}

//Pone al máximo la munición tanto en _ammo como en el cargador _clip
void Gun::resetAmmo()
{
	_ammo = _maxAmmo;
	_clip = _maxClip;
}

//Reduce la munición 
void Gun::useAmmo()
{
	/*
	if (_clip - _bulletsPerShot >= 0)
	{
		_clip -= _bulletsPerShot;
	}
	*/

	_clip = max(0, _clip - _bulletsPerShot);

	/*
	if(_clip == 0) reload();
	*/
}

void Gun::shoot() {
	if (_clip >= _bulletsPerShot //Si hay suficientes balas en el cargador
		&& _shooterComp != nullptr) //Si tiene un shooter, llama a su shoot()
	{
		_shooterComp->shoot();

		//Reduce la munición actual
		useAmmo();

		//Dispara
		cout << "Piumm!" << endl;
		cout << "Ammo: " << _ammo << "/" << _maxAmmo << endl;
		cout << "Clip: " << _clip << "/" << _maxClip << endl;

		
	}
	else //Si no, recarga
	{
		reload();
	}

}


//Muestra la información del arma por consola
void Gun::debugInfo() {
	cout << endl << _name << endl << _maxAmmo << endl << _ammo << endl << _maxClip << endl << _clip << endl << _bulletsPerShot << endl;
}