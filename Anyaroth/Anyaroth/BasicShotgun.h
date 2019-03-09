#pragma once
#include "Gun.h"

class BasicShotgun : public Gun
{
public:
	BasicShotgun(Game* game);
	~BasicShotgun();

	virtual void shoot();
};

