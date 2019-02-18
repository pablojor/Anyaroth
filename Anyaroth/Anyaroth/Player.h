#pragma once
#include "GameComponent.h"
#include "Arm.h"
#include "Gun.h"
#include "Shooter.h"

class Arm;
class Game;

class AnimatedSpriteComponent;
class PlayerControllerComponent;

class Player : public GameComponent
{
private:
	int _life;

public:
  	enum states { Idle, Attacking };
  	uint _currentState = 0;
	Arm* _weaponArm = nullptr;
	AnimatedSpriteComponent* _anim;
	PlayerControllerComponent* _controller;
  
	Player(Texture* texture, Game* g, string tag);
  	~Player();

	void update();
	virtual void beginCollision(GameComponent* other);
	virtual void endCollision(GameComponent* other);
  
	void setArm(Arm* arm) { _weaponArm = arm; };
	void equipGun(int gunIndex);
  
	uint getCurrentState() { return _currentState; };
	void setCurrentState(uint n) { _currentState = n; };
};