#pragma once

#include "InputComponent.h"
#include "TransformComponent.h"
#include "AnimatedSpriteComponent.h"
#include "FollowingComponent.h"

class GameComponent;

class ArmControllerComponent : public InputComponent
{
private:
	FollowingComponent* _followC;
	GameComponent* _player;
	AnimatedSpriteComponent* _anim;
	TransformComponent* _transform = nullptr;
	bool _leftClickPul = false; //_rightClickPul = false;
	double _minAimDistance;
public:
	ArmControllerComponent(GameComponent* obj);
	virtual void handleInput(const SDL_Event& event);
};

