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
	GameComponent* _obj;
	AnimatedSpriteComponent* _anim;
	TransformComponent* _transform = nullptr;
	bool _leftClickPul = false;
	bool _rPul = false;
	double _minAimDistance;

	double magicNumber = 64;

	bool isReloading = false;
	int _resolutionMultiplier = 0;
public:
	ArmControllerComponent(GameComponent* obj);
	virtual void handleInput(const SDL_Event& event);
};

