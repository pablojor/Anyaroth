#pragma once
#include "Melee.h"

class Axe :	public Melee
{
private:
	double _angle = 90;
public:
	Axe(Game* g);
	virtual ~Axe();
	void update(double time);
};

