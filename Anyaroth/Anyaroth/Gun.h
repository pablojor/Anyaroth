#pragma once
#include "GameComponent.h"
#include "BodyComponent.h"
#include "TransformComponent.h"
#include "Game.h"
#include "Shooter.h"

class Gun
{
private:
	/*
		_maxAmmo -> m�xima munici�n que almacena el arma
		_ammo -> munici�n almacenada actualmente en el arma

		_maxClip -> m�xima munici�n que almacena el arma en el cargador
		_clip -> munici�n almacenada actualmente en el cargador
	*/

	int _maxAmmo = 0, _ammo = 0, //Munici�n m�xima / munici�n actual
		_maxClip = 0, _clip = 0, //Munici�n m�xima en el cargador/ munici�n actual en el cargador
		_bulletsPerShot; //Balas usadas por disparo / r�faga

	string _name = ""; //El nombre del arma
	
	GameComponent* _shootingObj = nullptr; //El objeto que usa el arma
	Shooter* _shooterComp; //El componente con el m�todo shoot() del arma

	/*********************************
	//RECORDATORIO: Da�o de las armas
					Velocidad de disparo
					Rango

	/*********************************/

	void useAmmo();
	void reloadAux(int newClipValue);
	
public:
	Gun(GameComponent* shootingObj, Shooter* shooterComp, string name, int maxAmmunition, int magazine, int bulletsPerShot = 1);
	virtual ~Gun();

	void setShooter(Shooter* sh) { _shooterComp = sh; };
	bool shoot();

	void addAmmo(int ammoAdded);
	bool reload();
	void resetAmmo();

	int getAmmo() { return _ammo; };

	void debugInfo();

};