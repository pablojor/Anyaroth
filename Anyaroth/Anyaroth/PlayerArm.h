#pragma once
#include "Arm.h"
#include "Game.h"
#include "Cursor.h"

class Player;
class Gun;
class ArmControllerComponent;

class PlayerArm : public Arm
{
protected:
	Player* player = nullptr;
	ArmControllerComponent* _controller = nullptr;
	Cursor* _cursor = nullptr;
	
	double _minAimDistance = 48;

public:
	PlayerArm(Texture* texture, Player* player, Game* g, PlayState* play, Vector2D offset = { 0,0 });

	void update();

	void shoot();	
	bool reload(); 
	void setCursor(Cursor* c); //usado por el controller
};