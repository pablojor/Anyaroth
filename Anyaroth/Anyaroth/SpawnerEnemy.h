#pragma once
#include "Enemy.h"

class SpawnerEnemy : public Enemy
{
private:
	bool _spawning = false, _activated = false;
	double _spawnTime = 5000;
	int _dir = 8;

	bool _bloqueDer = false, _bloqueIzq = false, _move = false;

public:
	SpawnerEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual ~SpawnerEnemy() {}

	virtual void update(const double& deltaTime);

	virtual void subLife(int damage);

	virtual void beginCollision(GameObject* other, b2Contact* contact);
};