#pragma once
#include "GameObject.h"
#include "Layer.h"
#include "ObjectLayer.h"
#include "BulletPool.h"
#include "ExplosiveBulletPool.h"
#include "BouncingBulletPool.h"
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
	ExplosiveBulletPool* _explosivePool = nullptr;
	BouncingBulletPool* _bouncingPool = nullptr;

	GameObject* _layers;
	GameObject* _objects;
	Boss1* _boss1 = nullptr;

	vector <ObjectLayer*> _objectLayers;

	int _coinValue;

public:
	Map(string filename, Game* game, Player* player, Texture* tileset, BulletPool* bulletPool, ExplosiveBulletPool* explosivePool, BouncingBulletPool* bouncingPool, PlayStateHUD* hud, int coinValue);
	~Map();

	void createObjects();
	void restartLevel();

	virtual bool handleEvent(const SDL_Event& event);
	virtual void update(const double& deltaTime);
	virtual void render(Camera* c) const;
};