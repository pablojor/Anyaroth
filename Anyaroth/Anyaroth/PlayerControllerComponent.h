#pragma once

#include "InputComponent.h"
#include "MovingComponent.h"
#include "AnimatedSpriteComponent.h"

class GameComponent;

class PlayerControllerComponent : public InputComponent
{
	private:
		AnimatedSpriteComponent* _anim;
		MovingComponent* _movement = nullptr;
		bool _wPul = false, _aPul = false, _sPul = false, _dPul = false;
		bool _rightClickPul = false;

	public:
		PlayerControllerComponent(GameComponent* obj);
		virtual void handleInput(const SDL_Event& event);
};