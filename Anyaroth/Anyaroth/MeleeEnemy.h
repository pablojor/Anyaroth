#pragma once
#include "Enemy.h"

class MeleeEnemy : public Enemy
{
private:
	Vector2D _dir = Vector2D();
	int _realRange = 15;

public:
	MeleeEnemy(Game* g, PlayState* playstate, Texture* texture, Vector2D posIni, string tag);
	virtual ~MeleeEnemy() {}

	virtual void update(const double& deltaTime);

	void idle();
	void moving(Vector2D& dir);

	void attack();
	void attacking(const double& deltaTime);
};