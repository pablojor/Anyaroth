#pragma once
#include "ShooterInterface.h"

class ShotgunShooter :
	public ShooterInterface
{
private:
	vector<double> _bulletAngles;
public:
	//El vector de bulletAngles indica a la vez el número de balas y el angulo relativo que van a tener
	ShotgunShooter(const vector<double> &bulletAngles);
	virtual ~ShotgunShooter();

	void setBulletAngles(const vector<double> &bulletAngles) { _bulletAngles = bulletAngles; };
	virtual void shoot(Vector2D bulletPosition, Vector2D bulletDir, double angle);
};

