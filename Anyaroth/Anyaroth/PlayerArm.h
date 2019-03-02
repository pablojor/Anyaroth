#pragma once

#include "Arm.h"
#include "Game.h"

class Gun;
class ArmControllerComponent;

class PlayerArm : public Arm
{
protected:
	
	ArmControllerComponent* _controller;
	
	double _minAimDistance = 48;

	Gun* _currentGun = nullptr;
public:
	PlayerArm(Texture* texture, GameComponent* player, Game* g, PlayState* play, Vector2D offset = { 0,0 });
	virtual ~PlayerArm();

	void update();

	void setGun(Gun* gun); //Establece el arma
	void shoot();	
	bool reload(); 
};

