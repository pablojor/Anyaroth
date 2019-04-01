#pragma once
#include "Melee.h"

class Axe :	public Melee
{
private:
	double _angle, _iniAngle;
	int _usedDir = 1;

public:
	Axe(Game * g, Vector2D offset, Uint16 collidesWith, double damage, double w, double h, double iniAngle);
	virtual ~Axe() {}
	
	virtual void meleeAttack(double x, double y, int dir);
	void update(const double& deltaTime);
};