#pragma once
#ifndef Tile_H
#define Tile_H

#include "GameComponent.h"
#include "Texture.h"

class Tile : public GameComponent {
	public:
		Tile(double x, double y, int c, int f, Texture* t);
		~Tile();
		
};
#endif // Tile_H