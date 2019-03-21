#pragma once
#include "Gun.h"

class BasicShotgun : public Gun
{
private:
	int _angleBetweenBullet = 10;

public:
	BasicShotgun(Game* game);
	~BasicShotgun();

	virtual void shoot(BulletPool* bulletPool, const Vector2D& position, const double& angle, const string& tag);
};