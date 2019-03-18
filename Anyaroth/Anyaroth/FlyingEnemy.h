#pragma once
#include "Enemy.h"

class FlyingEnemy :	public Enemy
{
private: 
	double _amplitude = 25, _angularFrequency = 0.05, _velocity = 0.5, _k = _angularFrequency / _velocity;
	Vector2D _playerPos, _originalPos;
	TransformComponent* _playerTransform;
public:
	FlyingEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual ~FlyingEnemy();
	void update(double time);
};

