#pragma once
#include "GameObject.h"
#include "Layer.h"
#include "ObjectLayer.h"
#include "BulletPool.h"
#include "PlayStateHUD.h"
#include "NPC.h"
#include <vector>

class Player;
class Boss1;

class Map : public GameObject
{
private:
	Player* _player = nullptr;
	PlayStateHUD* _hud = nullptr;
	BulletPool* _bulletPool = nullptr;

	GameObject* _layers = nullptr;
	GameObject* _objects = nullptr;
	Boss1* _boss1 = nullptr;
	NPC* _npc = nullptr;

	vector <ObjectLayer*> _objectLayers;

	int _coinValue, _faseMisil=0;

public:
	Map(string filename, Game* game, Player* player, Texture* tileset, BulletPool* bulletPool, PlayStateHUD* hud, int coinValue);
	~Map();

	void createObjects();
	void restartLevel();

	virtual bool handleEvent(const SDL_Event& event);
	virtual void update(const double& deltaTime);
	virtual void render(Camera* c) const;
};