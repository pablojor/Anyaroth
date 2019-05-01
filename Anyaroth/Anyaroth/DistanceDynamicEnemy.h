#pragma once
#include "DistanceEnemy.h"
#include "GroundEnemy.h"

class DistanceDynamicEnemy : public DistanceEnemy, public GroundEnemy
{
private:
	Vector2D _dir = Vector2D();

public:
	DistanceDynamicEnemy(Game* g, Player* player, Vector2D pos, BulletPool* pool = nullptr);

	virtual void update(const double& deltaTime);
	virtual void attacking(const double& deltaTime);
	virtual void die();
	void addSensors();
};