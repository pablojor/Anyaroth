#pragma once
#include "Collectable.h"

class Coin : public Collectable
{
public:
	Coin(Game* game, Vector2D pos, int value);
	~Coin() {}
};