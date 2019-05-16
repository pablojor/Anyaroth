#pragma once
#include "Gun.h"
class Shotgun : public Gun
{
protected:
	int _angleBetweenBullet;
	int _numBulletsPerShot;
	BulletAnimType _bulletAnimType = ShotGunBullet;

public:
	Shotgun(Game* game, Texture* armTexture, Texture* bulletTexture, string shotSoundTag, double speed, double damage, double range, int maxClip, int maxMagazine, double maxCadence, BulletEffect* effect, GunType id, Texture* iconTexture, bool automatic = false, BulletAnimType bType = Default);
	virtual ~Shotgun();

	virtual void shoot(BulletPool* bulletPool, const Vector2D& position, double angle, const string& tag);
	virtual void enemyShoot(BulletPool* bulletPool, const Vector2D& position, double angle, const string& tag);
};

