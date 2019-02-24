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
	int AmountOfCollision;

public:
  	enum states { Idle, Attacking };
  	uint _currentState = 0;
	Arm* _weaponArm = nullptr;
	AnimatedSpriteComponent* _anim;
	PlayerControllerComponent* _controller;
	TransformComponent * _transform;
	BodyComponent * _body;
	uint32 _dashCD = 3000;
	uint32 _timer = 0;
	int _MaxDash = 2;


  
	Player(Texture* texture, Game* g, string tag);
  	~Player();

	void update();
	virtual void beginCollision(GameComponent* other);
	virtual void endCollision(GameComponent* other);
	
	void setLife(double amount);
	void addLife(double amount);
	void subLife(double amount);
	void die();

	void setArm(Arm* arm) { _weaponArm = arm; };
	void equipGun(int gunIndex);
  
	uint getCurrentState() { return _currentState; };
	void setCurrentState(uint n) { _currentState = n; };
};