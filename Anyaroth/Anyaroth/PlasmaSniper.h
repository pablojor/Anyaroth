#pragma once
#include "Gun.h"
#include "PiercingBulletEffect.h"

class PlasmaSniper :
	public Gun
{
private:
	PiercingBulletEffect _effect;
public:
	PlasmaSniper(Game* game);
	~PlasmaSniper();
};

