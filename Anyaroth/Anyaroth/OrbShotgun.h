#pragma once
#include "Shotgun.h"
#include "BouncingBulletEffect.h"
class OrbShotgun : public Shotgun
{
private:
	BouncingBulletEffect _effect = BouncingBulletEffect(10);
public:
	OrbShotgun(Game* g);
	virtual ~OrbShotgun();
};

