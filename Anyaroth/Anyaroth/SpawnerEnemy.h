#pragma once
#include "Enemy.h"

class SpawnerEnemy : public Enemy
{
private:
	bool _spawning = false, _activated = true;
	double _spawnTime = 1000;

public:
	SpawnerEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual ~SpawnerEnemy() {}
	virtual void update(double time);
	virtual void subLife(int damage);
};