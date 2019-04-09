#pragma once
#include "Gun.h"
#include "BulletEffect.h"

class BasicPistol : public Gun
{
private:
	BulletEffect _effect;
public:
	BasicPistol(Game* game);
	~BasicPistol();
};