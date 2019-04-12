#pragma once
#include "Enemy.h"

class SpawnerEnemy : public Enemy
{
protected:
	bool _move= false, _bloqueDer = false, _bloqueIzq = false;
	double _spawnTime = 5000, _maxEnemies = 4, _currentEnemies = 0;
	Vector2D _dir = Vector2D(1,0);

public:
	SpawnerEnemy(Game* g, Player* player, Vector2D pos);
	virtual ~SpawnerEnemy() {}

	void move();
	virtual void dropCapsule(const double& deltaTime) {};

	int deadEnemies();
	virtual void update(const double& deltaTime);
	virtual void subLife(int damage);

	virtual void beginCollision(GameObject* other, b2Contact* contact);
};