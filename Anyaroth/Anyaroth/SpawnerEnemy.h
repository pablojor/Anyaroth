#pragma once
#include "Enemy.h"

class SpawnerEnemy : public Enemy
{
private:
	bool _spawning = false, _activated = false;
	double _spawnTime = 1000;
	int _dir = 8;

	bool _bloqueDer = false, _bloqueIzq = false, _move = false;

public:
	SpawnerEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual ~SpawnerEnemy() {}
	virtual void update(double time);
	virtual void subLife(int damage);
	virtual void beginCollision(GameComponent* other, b2Contact* contact);
};