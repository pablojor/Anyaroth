#pragma once
#include "GameComponent.h"
#include "BodyComponent.h"
#include "TransformComponent.h"
#include "Game.h"
#include "ShooterInterface.h"
#include "BulletPool.h"
#include "GunType_def.h"

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
	double _cadence, _fireTimer = 0;

	GunType _type; //El nombre del arma
	
	GameComponent* _shootingObj = nullptr; //El objeto que usa el arma
	ShooterInterface* _shooterComp; //El componente con el m�todo shoot() del arma
	PoolWrapper* _bPool = nullptr;


	/*********************************
	//RECORDATORIO: Da�o de las armas (Está en Bullet)
					Velocidad de disparo
					Rango (En Bullet ?)

	/*********************************/

	void useAmmo();
	void reloadAux(int newClipValue);
	
public:
	Gun(GameComponent* shootingObj, ShooterInterface* shooterComp, PoolWrapper* bp, GunType type, int maxAmmunition, int magazine, double cadence, int bulletsPerShot = 1);
	virtual ~Gun();

	void setShooter(ShooterInterface* sh);
	void setBulletPool(PoolWrapper* bp) { _bPool = bp; };
	bool shoot(Vector2D bulletPosition, Vector2D bulletDir, bool flipped);
	void enemyShoot(Vector2D bulletPosition, Vector2D bulletDir, bool flipped);

	void addAmmo(int ammoAdded);
	bool reload();
	void resetAmmo();

	bool inline canShoot() { return SDL_GetTicks() > _fireTimer + _cadence; }

	int getAmmo() { return _ammo; };
	int getClip() { return _clip; }
	GunType getType() { return _type; };

	void debugInfo();

};