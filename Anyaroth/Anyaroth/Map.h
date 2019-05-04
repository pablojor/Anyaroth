#pragma once
#include "GameObject.h"
#include "Tilemap.h"
#include "ObjectLayer.h"
#include "BulletPool.h"
#include "PlayStateHUD.h"
#include <vector>

class Player;
class Boss1;
class Boss2;
class Boss3;

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
	Boss2* _azura = nullptr;
	Boss3* _angra = nullptr;
	int _misilFase = 0, _height = 0, _width = 0, _spawnType=0;

public:
	Map(string filename, Game* game, Player* player, Texture* tileset, BulletPool* bulletPool, PlayStateHUD* hud);
	~Map();

	void createObjects();
	void restartLevel();

	virtual bool handleEvent(const SDL_Event& event);
	virtual void update(const double& deltaTime);
	virtual void render(Camera* c) const;

	inline int getHeight() const { return _height; }
	inline int getWidth() const { return _width; }
};