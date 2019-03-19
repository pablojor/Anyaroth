#pragma once
#include "Enemy.h"

class FlyingEnemy :	public Enemy
{
private: 
	Vector2D _playerPos, _originalPos, _prevPos, pos, _bodyPos, _velocity = Vector2D(0.5,0.5);
	double _amplitude = 25, _damage = 50, _angularFrequency = 0.05, _k = _angularFrequency / _velocity.distance(Vector2D());
	BodyComponent* _playerBody;
public:
	FlyingEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual ~FlyingEnemy();
	void update(double time);
	void beginCollision(GameComponent * other, b2Contact* contact);
};

