#pragma once
#include "GameObject.h"
#include <map>
#include "Texture.h"
#include <string>
#include <utility>

class Tilemap : public GameObject
{

private:
	Texture* _tileSet = nullptr;

	int _maxFils = 0, _maxCols = 0;
	int _tileSize = 0;

	struct Tile {
		int index;
	};

	//Grid mapa
	map<int, Tile> _grid;


public:
	Tilemap(Game* game, Texture* tileSet);
	~Tilemap();

	virtual bool handleEvent(const SDL_Event& event) { return false; }
	virtual void update(const double& deltaTime);
	virtual void render(Camera* c) const;

	void loadTileMap(const string& filename);
};

