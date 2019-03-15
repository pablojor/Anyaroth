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
	PlayState* _play = nullptr;
	Player* _player = nullptr;

	map < string, Layer*> _layers;
	vector<string> _layersNames;

	map < string, ObjectLayer* > _objects;
	vector<string> _objectsNames;

public:
	Map(string filename, Texture* tileset, Game* game, PlayState* play, Player* player, list<GameObject*>& list);
	~Map();

	void createObjects(list<GameObject*>& list);
};