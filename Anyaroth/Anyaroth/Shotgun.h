#pragma once
#include "Gun.h"
class Shotgun :
	public Gun
{
protected:
	int _angleBetweenBullet;
	int _numBulletsPerShot;
	BulletAnimType _bulletAnimType = ShotGunBullet;
public:
	Shotgun(Texture* armTexture, Texture* bulletTexture, double speed, double damage, double range, int maxClip, int maxMagazine, double maxCadence, BulletEffect* effect, bool automatic = false, BulletAnimType bType = Default,Texture* iconTexture = nullptr);
	virtual ~Shotgun();

	virtual void shoot(PoolWrapper* bulletPool, const Vector2D& position, const double& angle, const string& tag);
};

