#pragma once
#include "GroundEnemy.h"

class MeleeEnemy : public GroundEnemy
{
public:
	MeleeEnemy(Game* g, Player* player, Vector2D pos);
	virtual ~MeleeEnemy() {}

	virtual void update(double deltaTime);
	virtual void attacking(double deltaTime);

	virtual void idle();
};