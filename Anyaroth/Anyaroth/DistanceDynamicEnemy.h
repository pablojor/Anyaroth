#pragma once
#include "DistanceEnemy.h"

class DistanceDynamicEnemy : public DistanceEnemy
{
private:
	Vector2D _dir = Vector2D();

public:
	DistanceDynamicEnemy(Game* g, Player* player, Vector2D pos, BulletPool* pool);

	virtual void update(const double& deltaTime);

	void idle();
	void moving(Vector2D& dir);
	void attack();
	void attacking(const double& deltaTime);
};