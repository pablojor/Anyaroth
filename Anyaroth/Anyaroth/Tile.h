#pragma once

#include "GameComponent.h"

class Tile : public GameComponent 
{
	public:
		Tile(double x, double y, int c, int f, Texture* t);
		~Tile() {}
};