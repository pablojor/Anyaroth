#pragma once

#include "InputComponent.h"
#include "TransformComponent.h"
#include "AnimatedSpriteComponent.h"

class GameComponent;

class ArmControllerComponent : public InputComponent
{
private:
	AnimatedSpriteComponent* _anim;
	TransformComponent* _transform = nullptr;
	bool _leftClickPul = false; //_rightClickPul = false;
public:
	ArmControllerComponent(GameComponent* obj);
	virtual void handleInput(const SDL_Event& event);
};

