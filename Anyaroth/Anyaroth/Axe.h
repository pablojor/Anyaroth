#pragma once
#include "Melee.h"

class Axe :	public Melee
{
private:
	double _angle, _iniAngle;

public:
	Axe(Game* g, double iniAngle, Vector2D offset);
	virtual ~Axe() {}

	void update(double time);
};