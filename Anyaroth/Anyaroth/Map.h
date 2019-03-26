#pragma once
#include "GameComponent.h"
#include "Layer.h"
#include "ObjectLayer.h"
#include <vector>

class PlayState;
class Player;

class Map : public GameComponent
{
private:
	Game* _game = nullptr;
	PlayState* _playState = nullptr;
	Player* _player = nullptr;

	vector<Layer*> _layers;

	map < string, ObjectLayer* > _objectLayers;
	vector<string> _objectLayersNames;

	vector<GameComponent*> _objects;

	int _coinValue;

public:
	Map(string filename, Game* game, PlayState* playstate, Texture* tileset, int coinValue);
	~Map();

	void createObjects();
	void restartLevel();

	virtual bool handleInput(const SDL_Event& event);
	virtual void update(double time);
	virtual void render(Camera* c) const;
};