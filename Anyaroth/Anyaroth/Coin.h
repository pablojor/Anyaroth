#pragma once
#include "Collectable.h"

class Coin : public Collectable
{
	public:
		Coin(Game* g, Texture* texture, Vector2D iniPos, int value) : Collectable(g, texture, iniPos, value, "Moneda") {};
		~Coin() {};
};

