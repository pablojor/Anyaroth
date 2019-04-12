#pragma once
#include "Shotgun.h"

class ImprovedShotgun :
	public Shotgun
{
private:
	BulletEffect _effect;
public:
	ImprovedShotgun(Game * game);
	virtual ~ImprovedShotgun();
};

