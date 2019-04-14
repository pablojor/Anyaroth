#pragma once
#include "Gun.h"
#include "BouncingBulletEffect.h"

class BossOrbCannon :
	public Gun
{
private:
	BouncingBulletEffect _effect = BouncingBulletEffect(10);
public:
	BossOrbCannon(Game* game);
	virtual ~BossOrbCannon();
};

