#pragma once
#include "Collectable.h"

class AmmoPackage : public Collectable
{
public:
	AmmoPackage(Game* game, Vector2D pos, int value);
	virtual ~AmmoPackage() {}
};