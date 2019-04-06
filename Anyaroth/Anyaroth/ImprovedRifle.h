#pragma once
#include "Gun.h"
class ImprovedRifle :
	public Gun
{
private:
	BulletEffect _effect;
public:
	ImprovedRifle(Game* game);
	virtual ~ImprovedRifle();
};

