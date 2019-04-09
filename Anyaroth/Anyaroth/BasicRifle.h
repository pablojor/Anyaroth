#pragma once
#include "Gun.h"
class BasicRifle :
	public Gun
{
private:
	BulletEffect _effect;
public:
	BasicRifle(Game* game);
	virtual ~BasicRifle();
};

