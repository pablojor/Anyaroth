#pragma once

#include "GameComponent.h"

class Tile : public GameComponent 
{
	public:
		Tile(double x, double y, int f, int c, Texture* t);
		~Tile() {}
};