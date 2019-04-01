#pragma once
#include "Enemy.h"

class StaticSpawnerEnemy : public Enemy
{
private:
	double _spawnTime = 3000, _maxEnemies = 4, _currentEnemies = 0;

public:
	StaticSpawnerEnemy(Game* g, Player* player, Vector2D pos);
	virtual ~StaticSpawnerEnemy() {}

	int activeEnemies();
	virtual void update(const double& deltaTime);
};