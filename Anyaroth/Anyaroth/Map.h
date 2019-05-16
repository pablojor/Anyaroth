#pragma once
#include "GameObject.h"
#include "Tilemap.h"
#include "ObjectLayer.h"
#include "BulletPool.h"
#include "PlayStateHUD.h"
#include <vector>

class Player;

class Map : public GameObject
{
private:
	Player* _player = nullptr;
	BulletPool* _bulletPool = nullptr;

	Tilemap* _tilemap = nullptr;
	GameObject* _objects = nullptr;
	vector <ObjectLayer*> _objectLayers;

	double _height = 0, _width = 0, _spawnType = 0;

public:
	Map(string filename, Game* game, Player* player, Texture* tileset, BulletPool* bulletPool);
	~Map();

	void createObjects();
	void restartLevel();

	virtual bool handleEvent(const SDL_Event& event);
	virtual void update(double deltaTime);
	virtual void render(Camera* c) const;

	inline double getHeight() const { return _height; }
	inline double getWidth() const { return _width; }
};