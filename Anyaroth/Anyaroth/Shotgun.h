#pragma once
#include "Gun.h"
class Shotgun :
	public Gun
{
protected:
	int _angleBetweenBullet;
	int _numBulletsPerShot;
public:
	Shotgun(Texture* armTexture, Texture* bulletTexture, double speed, double damage, double range, int maxClip, int maxMagazine, double maxCadence, bool automatic = false);
	virtual ~Shotgun();

	virtual void shoot(PoolWrapper* bulletPool, const Vector2D& position, const double& angle, const string& tag);
	virtual void enemyShoot(PoolWrapper* bulletPool, const Vector2D& position, const double& angle, const string& tag);
};

