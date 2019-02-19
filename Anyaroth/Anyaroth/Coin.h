#pragma once
#include "Collectable.h"

class Coin : public Collectable
{
	public:
		Coin(Texture* texture, Vector2D iniPos, int value,Game* g, string tag) : Collectable(texture, iniPos, value, g, tag) {};
		~Coin() {};
};

