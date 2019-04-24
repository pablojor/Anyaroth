#pragma once
#include "Gun.h"
#include "GravityBulletEffect.h"
#include "ExplosiveBulletEffect.h"

class GravityBombCannon :
	public Gun
{
private:
	GravityBulletEffect _effect = GravityBulletEffect(3000);
public:
	GravityBombCannon(Game* game);
	virtual ~GravityBombCannon();
};

