#pragma once
#ifndef Layer_H
#define Layer_H

#include "Tile.h"
#include <string>

class Layer {
public:
	Layer(int type);
	~Layer();
	bool LoadTilemap(string filename);

protected:
	int type;
	SDL_Surface* Surf_Tileset;
	vector<Tile*> tilemap;
};
#endif // Layer_H