#pragma once
#include "GameComponent.h"
#include "Layer.h"
#include "ObjectLayer.h"
#include <map>
#include <vector>
#include <list>

class PlayState;
class Player;

class Map : public GameComponent
{
private:
	Game* _game = nullptr;
	PlayState* _playState = nullptr;
	Player* _player = nullptr;

	map < string, Layer*> _layers;
	vector<string> _layersNames;

	map < string, ObjectLayer* > _objects;
	vector<string> _objectsNames;

	int _coinValue = 10;

public:
	Map(string filename, Texture* tileset, Game* game, PlayState* playstate, Player* player);
	~Map();

	void createObjects();
};