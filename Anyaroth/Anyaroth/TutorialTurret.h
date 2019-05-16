#pragma once
#include "DistanceStaticEnemy.h"

class TutorialTurret : public DistanceStaticEnemy
{
public:
	TutorialTurret(Game* g, Player* player, Vector2D pos, BulletPool* pool);
	virtual ~TutorialTurret() {}

	virtual void beginCollision(GameObject* other, b2Contact* contact);
	virtual void shoot();
	virtual void update(double deltaTime);
};