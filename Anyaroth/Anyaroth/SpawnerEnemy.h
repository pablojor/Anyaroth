#pragma once
#include "Enemy.h"

class SpawnerEnemy : public Enemy
{
private:
	double _spawnTime = 5000, _maxEnemies = 4, _currentEnemies = 0;
	Vector2D _dir = Vector2D();

public:
	SpawnerEnemy(Game* g, Player* player, Vector2D pos);
	virtual ~SpawnerEnemy() {}

	void move();
	void dropCapsule(const double& deltaTime);

	int deadEnemies();
	virtual void update(const double& deltaTime);
	virtual void subLife(int damage);
};