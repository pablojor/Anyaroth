#pragma once
#include "Enemy.h"

class FlyingEnemy : public Enemy
{
private:
	Vector2D _pos, _originalPos, _previousPos, _dir, _velocity = Vector2D(0.5, 0.5);
	double _maxDistance = 300, _amplitude = 25, _angularFrequency = 0.05, _k = _angularFrequency / _velocity.distance(Vector2D());

public:
	FlyingEnemy(Game* g, Player* player, Vector2D pos);
	virtual ~FlyingEnemy() {}

	void sinusoidalMove(double deltaTime);
	virtual void update(double deltaTime);
	virtual void beginCollision(GameObject * other, b2Contact* contact);
};