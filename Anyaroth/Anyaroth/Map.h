#pragma once
#include "GameObject.h"
#include "Layer.h"
#include "ObjectLayer.h"
#include "BulletPool.h"
#include "ExplosiveBulletPool.h"
#include <vector>

class Player;

class Map : public GameObject
{
private:
	Player* _player = nullptr;
	BulletPool* _bulletPool = nullptr;
	ExplosiveBulletPool* _explosivePool = nullptr;

	GameObject* _layers;
	GameObject* _objects;

	vector <ObjectLayer*> _objectLayers;

	int _coinValue;

public:
	Map(string filename, Game* game, Player* player, Texture* tileset, BulletPool* bulletPool, ExplosiveBulletPool* explosivePool, int coinValue);
	~Map();

	void createObjects();
	void restartLevel();

	virtual bool handleEvent(const SDL_Event& event);
	virtual void update(const double& deltaTime);
	virtual void render(Camera* c) const;
};