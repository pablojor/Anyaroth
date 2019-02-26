#pragma once

#include "InputComponent.h"
#include "TransformComponent.h"
#include "AnimatedSpriteComponent.h"
#include "FollowingComponent.h"

class GameComponent;
class Arm;

class ArmControllerComponent : public InputComponent
{
private:
	FollowingComponent* _followC;
	GameComponent* _player;
	Arm* _obj;
	AnimatedSpriteComponent* _anim;
	TransformComponent* _transform = nullptr;
	bool _leftClickPul = false, _canShoot = true;
	bool _rPul = false;

	bool isReloading = false;
public:
	ArmControllerComponent(GameComponent* obj);
	virtual void handleInput(const SDL_Event& event);

	int mouseX = 0; int mouseY = 0;
	int flipPosOffset = 8; //Distancia que se mueve el brazo al hacer flip
};

