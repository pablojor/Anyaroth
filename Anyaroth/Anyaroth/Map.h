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

	list<GameComponent*> _levelObjects;

	int _coinValue;

public:
	Map(string filename, Game* game, PlayState* playstate, Texture* tileset, int coinValue);
	~Map();

	void createObjects();

	virtual bool handleInput(const SDL_Event& event);
	virtual void update(double time);
	virtual void render(Camera* c) const;
};