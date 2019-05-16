#pragma once
#include "Enemy.h"

class StaticSpawnerEnemy : public Enemy
{
private:
	double _spawnTime = 1500, _maxEnemies = 5, _currentEnemies = 0;

public:
	StaticSpawnerEnemy(Game* g, Player* player, Vector2D pos);
	virtual ~StaticSpawnerEnemy() {}

	int activeEnemies();
	virtual void update(double deltaTime);
};