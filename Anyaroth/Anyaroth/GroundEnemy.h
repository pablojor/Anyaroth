#pragma once
#include "Enemy.h"

class GroundEnemy : public Enemy
{
protected:
	Vector2D _dir = Vector2D();

public:
	GroundEnemy(Game* g, Player* player, Vector2D pos, Texture* texture);
	virtual ~GroundEnemy() {}

	virtual void idle();
	virtual void moving(Vector2D& dir);
	virtual void attack();
	virtual void attacking(const double& deltaTime) = 0;
};