#pragma once

#include "GameComponent.h"
#include "TransformComponent.h"
#include "Game.h"
#include "Shooter.h"

class Gun
{
private:
	/*
		_maxAmmo -> máxima munición que almacena el arma
		_ammo -> munición almacenada actualmente en el arma

		_maxClip -> máxima munición que almacena el arma en el cargador
		_clip -> munición almacenada actualmente en el cargador
	*/
	int _maxAmmo = 0, _ammo = 0, //Munición máxima / munición actual
		_maxClip = 0, _clip = 0, //Munición máxima en el cargador/ munición actual en el cargador
		_bulletsPerShot; //Balas usadas por disparo / ráfaga

	string _name = ""; //El nombre del arma
	
	GameComponent* _shootingObj = nullptr; //El objeto que usa el arma
	Shooter* _shooterComp; //El componente con el método shoot() del arma

	/*********************************
	//RECORDATORIO: Daño de las armas
					Velocidad de disparo
					Rango

	/*********************************/

	void useAmmo();
	void reloadAux(int newClipValue);
	
public:
	Gun(GameComponent* shootingObj, Shooter* shooterComp, string name, int maxAmmunition, int magazine, int bulletsPerShot = 1);
	virtual ~Gun();

	void setShooter(Shooter* sh) { _shooterComp = sh; };
	void shoot();

	void addAmmo(int ammoAdded);
	bool reload();
	void resetAmmo();

	void debugInfo();

};

