#pragma once
#include "Melee.h"

class PoleAxe :	public Melee
{
private:
	Vector2D _pos, _nextPos, _velocity = { 5,0 };

public:
	PoleAxe(Game* game);
	~PoleAxe();

	inline void setVelocity(Vector2D velocity) { _velocity = velocity; }
	virtual void update(double deltaTime);
};