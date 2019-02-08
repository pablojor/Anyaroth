#pragma once

#include "InputComponent.h"
#include "MovingComponent.h"

#include "AnimatedSpriteComponent.h"

class PlayerControllerComponent : public InputComponent
{

	private:
		MovingComponent* movement;
		AnimatedSpriteComponent* anim;

		bool wPul = false, aPul = false, sPul = false, dPul = false;

	public:
		PlayerControllerComponent(MovingComponent* movement, AnimatedSpriteComponent* anim) :
			movement(movement), anim(anim), InputComponent() {};

		virtual void handleInput( const SDL_Event& event);

};