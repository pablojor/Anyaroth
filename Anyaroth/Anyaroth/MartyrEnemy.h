#pragma once
#include "Enemy.h"

class MartyrEnemy : public Enemy
{
private:
	int _explosionRange = 60, _impulse = 80, _canDie;

public:
	MartyrEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual void update(double time);
};