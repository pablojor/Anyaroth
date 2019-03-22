#pragma once
#include "Enemy.h"

class Capsule : public Enemy
{
private:
	bool _spawning = false;

public:
	Capsule(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual ~Capsule() {}

	virtual void update(const double& deltaTime);

	virtual void beginCollision(GameObject* other, b2Contact* contact);
};