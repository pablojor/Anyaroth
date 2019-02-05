#pragma warning(disable : 4996)
#ifndef Layer_H
#define Layer_H

#include "Tile.h"

class Layer {
public:
	Layer();
	~Layer();
	bool LoadTilemap(const char* filename);
protected:
	int type;
	SDL_Surface* Surf_Tileset;
	vector<Tile*> tilemap;
};
#endif // !Layer_H
