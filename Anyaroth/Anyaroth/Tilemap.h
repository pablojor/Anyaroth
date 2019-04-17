#pragma once
#include "GameObject.h"
#include "Texture.h"
#include <Box2D/Box2D.h>
#include <string>
#include <map>

class Tilemap : public GameObject
{
private:
	Texture* _tileSet = nullptr;

	int _maxFils = 0, _maxCols = 0;
	int _tileSize = 0;

	struct Tile : public GameObject
	{
		Tile() : GameObject(nullptr) {}
		Tile(int i, int xI, int yI) : GameObject(nullptr), tilesetIndex(i), xIndex(xI), yIndex(yI) {}

		int tilesetIndex = 0;
		int xIndex = 0;
		int yIndex = 0;
	};

	map<int, Tile> _grid;
	vector<b2Body*> _colliders;

public:
	Tilemap(Game* game, Texture* tileSet);
	~Tilemap();

	virtual bool handleEvent(const SDL_Event& event) { return false; }
	virtual void update(const double& deltaTime) {}
	virtual void render(Camera* c) const;

	void loadTileMap(const string& filename);
};