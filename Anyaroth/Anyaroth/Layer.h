#pragma once
#include <string>
#include "Tile.h"

class Layer : public GameComponent{
public:
	Layer(string name, Texture* t, string filename);
	~Layer();
	void render() const;

protected:
	//int type;
	Texture* tileset;
	vector<Tile*> tilemap;
};