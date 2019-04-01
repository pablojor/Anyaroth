#pragma once
#include "Map.h"
#include <list>

class LevelManager
{
private:
	Game* _game = nullptr;
	Player* _player = nullptr;
	PlayStateHUD* _hud = nullptr;
	Map* _currentMap = nullptr;

	BulletPool* _enemyBulletPool = nullptr;
	/*ExplosiveBulletPool* _enemyExplosivePool = nullptr;
	BouncingBulletPool* _enemyBouncingPool = nullptr;*/

	Texture* _tilesetZone1 = nullptr;

	list<GameObject*>* _objectList;

public:
	LevelManager() {}
	LevelManager(Game* game, Player* player, list<GameObject*>* objects, PlayStateHUD* hud);
	~LevelManager() {}

	void setLevel(int zone, int level);
	void changeLevel(int zone, int level);
	inline void resetLevel() { _currentMap->restartLevel(); _enemyBulletPool->stopBullets(); }

	inline Map* getCurrentMap() const { return _currentMap; }
};