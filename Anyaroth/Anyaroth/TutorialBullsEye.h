#pragma once
#include "Enemy.h"

class TutorialBullsEye : public Enemy
{
private:
	bool _hasBeenHit = false;

public:
	TutorialBullsEye(Game* g, Player* player, Vector2D pos);
	virtual ~TutorialBullsEye() {}

	virtual void update(const double& deltaTime);
	virtual void beginCollision(GameObject* other, b2Contact* contact);
};