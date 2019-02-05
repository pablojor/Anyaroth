#pragma once
#ifndef Tile_H
#define TIle_H

#include "GameComponent.h"

class Tile /*: public GameComponent*/ {
	public:
		Tile(int ID, double x, double y);
		~Tile();
	protected:
		int tileID;
};
#endif // !Tile_H

