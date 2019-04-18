#pragma once
#include "GameObject.h"
#include "Tilemap.h"
#include "ObjectLayer.h"
#include "BulletPool.h"
#include "PlayStateHUD.h"
#include <vector>

class Player;
class Boss1;

class Map : public GameObject
{
private:
	Player* _player = nullptr;
	PlayStateHUD* _hud = nullptr;
	BulletPool* _bulletPool = nullptr;

	Tilemap* _tilemap = nullptr;
	GameObject* _objects = nullptr;
	vector <ObjectLayer*> _objectLayers;

	Boss1* _spenta = nullptr;
	int _faseMisil = 0;

public:
	Map(string filename, Game* game, Player* player, Texture* tileset, BulletPool* bulletPool, PlayStateHUD* hud);
	~Map();

	void createObjects();
	void restartLevel();

	virtual bool handleEvent(const SDL_Event& event);
	virtual void update(const double& deltaTime);
	virtual void render(Camera* c) const;
};