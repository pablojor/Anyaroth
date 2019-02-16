#pragma once

#include "GameComponent.h"
#include "Arm.h"
#include "Gun.h"
#include "Shooter.h"

class Arm;
class Game;

class AnimatedSpriteComponent;
class PlayerControllerComponent;

class Player : public GameComponent {
private:
	int _life;
	Arm* _weaponArm = nullptr;

public:
  	enum states { Idle, Attacking };
  
	Player(Texture* texture, Game* g);
  ~Player();
  
	AnimatedSpriteComponent* _anim;
	PlayerControllerComponent* _controller;
  
  uint _currentState = 0;

	void update();
  
	void setArm(Arm* arm) { _weaponArm = arm; };
	void equipGun(int gunIndex);
  
	uint getCurrentState() { return _currentState; };
	void setCurrentState(uint n) { _currentState = n; };
};