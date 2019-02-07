#pragma once
#ifndef Layer_H
#define Layer_H

#include "Tile.h"
#include <string>
#include "Texture.h"
#include "GameObject.h"

class Layer : public GameObject{
public:
	Layer(int type, Texture* t, string filename);
	~Layer();
	void render(Uint32 time);
	virtual void update(Uint32 time) {};
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};

protected:
	int type;
	Texture* tileset;
	vector<Tile*> tilemap;
};
#endif // Layer_H