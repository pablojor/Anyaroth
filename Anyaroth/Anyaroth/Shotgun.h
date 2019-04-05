#pragma once
#include "Gun.h"
class Shotgun :
	public Gun
{
protected:
	int _angleBetweenBullet;
	int _numBulletsPerShot;
public:
	Shotgun(Texture* armTexture, Texture* bulletTexture, double speed, double damage, double range, int maxClip, int maxMagazine, double maxCadence, BulletEffect* effect, bool automatic = false);
	virtual ~Shotgun();

	virtual void shoot(BulletPool* bulletPool, const Vector2D& position, const double& angle, const string& tag);
};

