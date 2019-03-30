#pragma once
#include "Shotgun.h"

class BasicShotgun : public Shotgun
{
private: 
	BulletEffect _effect;
public:
	BasicShotgun(Game* game);
	~BasicShotgun();
};
