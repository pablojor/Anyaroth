#pragma once
#include "Melee.h"
class Poleaxe : public Melee
{
private:
	BodyComponent* _owner = nullptr;
	Vector2D _pos, _nextPos,_velocity = { 18,0 };
public:
	Poleaxe(Game * g, Vector2D offset, Uint16 collidesWith, double damage, double w, double h, GameObject* owner);
	virtual ~Poleaxe();
	void update(const double& deltaTime);
	//void chargeAttack();
	//void meleeAttack();
	//void thrustAttack();
};

