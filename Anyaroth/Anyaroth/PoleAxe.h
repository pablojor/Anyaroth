#pragma once
#include "Melee.h"


class PoleAxe :	public Melee
{
private:
	Vector2D _pos, _nextPos, _velocity = { 5,0 };

public:
	PoleAxe(Game* game);
	~PoleAxe();

	virtual void update(const double& deltaTime);
};

