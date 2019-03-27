#pragma once
#include "Map.h"
#include <list>

class LevelManager
{
private:
	Game* _game = nullptr;
	Player* _player = nullptr;
	Map* _currentMap = nullptr;

	BulletPool* _enemyBulletPool = nullptr;
	ExplosiveBulletPool* _enemyExplosivePool = nullptr;

	Texture* _tilesetZone1 = nullptr;

	list<GameObject*>* _objectList;

public:
	LevelManager() {}
	LevelManager(Game* game, Player* player, list<GameObject*>* objects);
	~LevelManager() {}

	void setLevel(int zone, int level);
	void changeLevel(int zone, int level);
	inline void resetLevel() { _currentMap->restartLevel(); }

	inline Map* getCurrentMap() const { return _currentMap; }
};