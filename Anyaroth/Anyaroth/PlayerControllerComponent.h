#pragma once
#include "InputComponent.h"
#include "MovingComponent.h"
#include "AnimatedSpriteComponent.h"
#include "FollowingComponent.h"

class GameComponent;

class PlayerControllerComponent : public InputComponent
{
	private:
		AnimatedSpriteComponent* _anim;
		GameComponent* _obj;
		MovingComponent* _movement = nullptr;
		bool _wPul = false, _aPul = false, _sPul = false, _dPul = false;
		bool _rightClickPul = false, _isAttacking = false, jump = false;

	public:
		PlayerControllerComponent(GameComponent* obj);
		virtual void handleInput(const SDL_Event& event);
		
		void changeJump();
		bool isAttacking() { return _isAttacking; };
		void setIsAttacking(bool b) { _isAttacking = b; };
};