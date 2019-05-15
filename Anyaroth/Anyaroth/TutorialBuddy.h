#pragma once
#include "GroundEnemy.h"

class TutorialBuddy : public GroundEnemy
{
public:
	TutorialBuddy(Game* g, Player* player, Vector2D pos);
	virtual ~TutorialBuddy() {}

	virtual void update(const double& deltaTime);
	virtual void attacking(const double& deltaTime) {};
	virtual void beginCollision(GameObject* other, b2Contact* contact);
};