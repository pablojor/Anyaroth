#pragma once
#include "Melee.h"

class Sword : public Melee
{
protected:
	double _angle, _iniAngle, _speed = -6;
	int _usedDir = 1;

public:
	Sword(Game* game);
	virtual ~Sword() {}
	
	virtual void meleeAttack(double x, double y, int dir);
	void update(double deltaTime);

	inline void setIniAngle(double angle) { _iniAngle = angle; _angle = _iniAngle; }
};