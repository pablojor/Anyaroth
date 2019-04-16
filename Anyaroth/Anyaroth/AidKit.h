#pragma once
#include "Collectable.h"

class AidKit : public Collectable
{
public:
	AidKit(Game* game, Vector2D pos, int value);
	virtual ~AidKit() {}
};