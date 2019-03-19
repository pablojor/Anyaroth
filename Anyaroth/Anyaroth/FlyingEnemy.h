#pragma once
#include "Enemy.h"

class FlyingEnemy :	public Enemy
{
private: 
	Vector2D _playerPos, _originalPos, _velocity = Vector2D(0.0005,0.00005);
	double _amplitude = 25, _angularFrequency = 0.5, acumulatedVel=0, _k = _angularFrequency / _velocity.distance(Vector2D());
	TransformComponent* _playerTransform;
public:
	FlyingEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual ~FlyingEnemy();
	void update(double time);
	void beginCollision(GameComponent * other, b2Contact* contact);
};

