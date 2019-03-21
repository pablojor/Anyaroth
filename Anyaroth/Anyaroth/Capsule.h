#pragma once
#include "Enemy.h"

class Capsule : public Enemy
{
private:
	bool _spawning = false;

public:
	Capsule(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual ~Capsule() {}
	virtual void update(double time);
	virtual void beginCollision(GameComponent* other, b2Contact* contact);
};