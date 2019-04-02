#pragma once
#include "PhysicsComponent.h"
#include "GameObject.h"
#include "GroundEnemy.h"

class GravityBombDebuff :
	public PhysicsComponent
{
private:
	bool _active = false;

	GameObject* _gravityZone = nullptr;
	GameObject* _obj = nullptr;
	double _absorbSpeed = 20.0;
	Vector2D _dir = { 0,0 };

	double _damageTime = 0;
	double _damageTickTime = 25;
	int _ticks = 0;
	double _minDistance = 10;



	void changeDir();
public:
	GravityBombDebuff(GameObject* obj, GameObject* gravityZone);
	virtual ~GravityBombDebuff();

	virtual void update(const double& deltaTime);
	void absorb();
	void stop();
	void setZone(GameObject* zone) { _gravityZone = zone; }
};

