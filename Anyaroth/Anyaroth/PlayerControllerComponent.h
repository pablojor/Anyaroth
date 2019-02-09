#pragma once

#include "InputComponent.h"
#include "MovingComponent.h"
//#include "AnimatedSpriteComponent.h"

class GameComponent;

class PlayerControllerComponent : public InputComponent
{

	private:
	  //AnimatedSpriteComponent* anim;
		MovingComponent* _movement = nullptr;
		bool wPul = false, aPul = false, sPul = false, dPul = false;

	public:
		PlayerControllerComponent(GameComponent* obj);
		virtual void handleInput(const SDL_Event& event);
};