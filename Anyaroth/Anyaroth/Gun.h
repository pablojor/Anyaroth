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
	int _maxAmmo = 0, _ammo = 0, //Municion maxima / municion actual
		_maxClip = 0, _clip = 0, //Municion maxima en el cargador/ municion actual en el cargador
		_bulletsPerShot; //Balas usadas por disparo / rafaga

	GunType _type; //El nombre del arma
	
	GameComponent* _shootingObj = nullptr; //El objeto que usa el arma
	ShooterInterface* _shooterComp = nullptr; //El componente con el metodo shoot() del arma
	PoolWrapper* _bPool = nullptr;

	//RECORDATORIO: Daño de las armas (Está en Bullet), Velocidad de disparo, Rango (En Bullet ?)

	void useAmmo();
	void reloadAux(int newClipValue);
	
public:
	Gun(GameComponent* shootingObj, ShooterInterface* shooterComp, PoolWrapper* bp, GunType type, int maxAmmunition, int magazine, int bulletsPerShot = 1);
	virtual ~Gun() {}

	void setShooter(ShooterInterface* sh);
	inline void setBulletPool(PoolWrapper* bp) { _bPool = bp; }
	bool shoot(Vector2D bulletPosition, Vector2D bulletDir, bool flipped);
	void enemyShoot(Vector2D bulletPosition, Vector2D bulletDir, bool flipped);

	void addAmmo(int ammoAdded);
	bool reload();
	void resetAmmo();

	inline int getAmmo() const { return _ammo; }
	inline int getClip() const { return _clip; }
	inline GunType getType() const { return _type; }
	void debugInfo();
};