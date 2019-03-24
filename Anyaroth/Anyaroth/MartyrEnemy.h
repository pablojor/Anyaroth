#pragma once
#include "Enemy.h"

class MartyrEnemy : public Enemy
{
private:
	Vector2D _dir = Vector2D();
	int _explosionRange = 60, _impulse = 15;

public:
	MartyrEnemy(Game* g, Player* player, Vector2D pos);

	virtual void update(const double& deltaTime);

	void explosionDie();

	void idle();
	void moving(Vector2D& dir);

	void attack();
	void attacking(const double& deltaTime);
};