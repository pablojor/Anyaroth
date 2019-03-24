#pragma once
#include "Enemy.h"

class MeleeEnemy : public Enemy
{
private:
	Vector2D _dir = Vector2D();

public:
	MeleeEnemy(Game* g, Player* player, Vector2D pos);
	virtual ~MeleeEnemy() {}

	virtual void update(const double& deltaTime);

	void idle();
	void moving(Vector2D& dir);

	void attack();
	void attacking(const double& deltaTime);
};