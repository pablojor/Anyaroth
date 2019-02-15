#pragma once

#include "GameComponent.h"

class AnimatedSpriteComponent;
class PlayerControllerComponent;

class Player : public GameComponent {
private:
	int _life;

	uint _currentState = 0;

	AnimatedSpriteComponent* _anim;
	PlayerControllerComponent* _controller;

public:
	enum states { Idle, Attacking };

	Player(Texture* texture);
	~Player();

	void update();

	uint getCurrentState() { return _currentState; };
	void setCurrentState(uint n) { _currentState = n; };
};