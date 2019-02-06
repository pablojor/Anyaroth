#pragma once
#ifndef Layer_H
#define Layer_H

#include "Tile.h"
#include <string>
#include "Texture.h"

class Layer {
public:
	Layer(int type, Texture* t);
	~Layer();
	bool LoadTilemap(string filename);
	void render(Uint32 time);

protected:
	int type;
	Texture* tileset;
	vector<Tile*> tilemap;
};
#endif // Layer_H