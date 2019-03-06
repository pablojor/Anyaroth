#pragma once

#include "Arm.h"
#include "Game.h"
#include "Cursor.h"

class Gun;
class ArmControllerComponent;

class PlayerArm : public Arm
{
protected:
	
	ArmControllerComponent* _controller;
	Cursor* _cursor;
	
	double _minAimDistance = 48;
	int _flipPosOffset = 8;

public:
	PlayerArm(Texture* texture, GameComponent* player, Game* g, PlayState* play, Vector2D offset = { 0,0 });

	void update();

	void shoot();	

	bool reload(); 
	void setCursor(Cursor* c); //usado por el controller
};

