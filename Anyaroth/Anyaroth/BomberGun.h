#pragma once
#include "Gun.h"
#include "ExplosiveBulletEffect.h"

class BomberGun :
	public Gun
{
private:
	ExplosiveBulletEffect _effect = ExplosiveBulletEffect(100);
public:
	BomberGun(Game* game);
	~BomberGun();
};

