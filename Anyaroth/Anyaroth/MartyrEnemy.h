#pragma once
#include "Enemy.h"
#include "MovingComponent.h"

class MartyrEnemy : public Enemy
{
private:
	int _explosionRange = 60, _impulse = 15;

public:
	MartyrEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual void update(double time);
};