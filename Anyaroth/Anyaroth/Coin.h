#pragma once
#include "Collectable.h"

class Coin : public Collectable
{
	public:
		Coin(Texture* texture, Vector2D iniPos, int value) : Collectable(texture, iniPos, value) {};
		~Coin() {};
};

