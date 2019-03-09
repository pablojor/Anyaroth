#pragma once
#include "Arm.h"

class Player;

class PlayerArm : public Arm
{
private:
	Player* _player = nullptr;

	void handleFlipState(const Vector2D& target);

public:
	PlayerArm(Game* g, Player* player, Vector2D offset = { 0, 0 });

	void update();

	void shoot();	
	bool reload(); 
};