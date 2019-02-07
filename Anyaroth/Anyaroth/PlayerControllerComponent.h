#pragma once

#include "InputComponent.h"
#include "MovingComponent.h"

class PlayerControllerComponent : public InputComponent
{

	private:
		MovingComponent* movement;
		bool wPul = false, aPul = false, sPul = false, dPul = false;

	public:
		PlayerControllerComponent(MovingComponent* movement) :
			movement(movement), InputComponent() {};

		virtual void handleInput( const SDL_Event& event);

};