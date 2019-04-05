#pragma once
#include "Gun.h"
#include "BouncingBulletEffect.h"

class BounceOrbCannon :
	public Gun
{
private:
	BouncingBulletEffect _effect = BouncingBulletEffect(4);
public:
	BounceOrbCannon(Game* game);
	virtual ~BounceOrbCannon();
};

