#pragma once
#include "Enemy.h"

class FlyingEnemy : public Enemy
{
private:
	Vector2D _playerPos, _bodyPos, _prevPos, _velocity = Vector2D(0.5, 0.5);
	double _amplitude = 25, _damage = 50, _angularFrequency = 0.05, _k = _angularFrequency / _velocity.distance(Vector2D());
	BodyComponent* _playerBody = nullptr;

public:
	FlyingEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual ~FlyingEnemy();

	void update(const double& deltaTime);

	void beginCollision(GameComponent * other, b2Contact* contact);
};