#pragma once
#include "GroundEnemy.h"

class MartyrEnemy : public GroundEnemy
{
private:
	int _explosionRange = 60, _impulse = 15;

public:
	MartyrEnemy(Game* g, Player* player, Vector2D pos);

	virtual void update(const double& deltaTime);
	virtual void attacking(const double& deltaTime);

	void explosionDie();
};