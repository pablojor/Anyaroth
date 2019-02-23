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
		bool _wPul = false, _aPul = false, _sPul = false, _dPul = false, _sfPul = false;
		bool _rightClickPul = false, _isAttacking = false, jump = false;
		bool jumping = false, _wallOnR = false, _wallOnL = false;

	public:
		PlayerControllerComponent(GameComponent* obj);
		virtual void handleInput(const SDL_Event& event);
		
		void changeJump();
		void ableJump();
		void wallOnLeft(bool yes);
		void wallOnRight(bool yes);

		bool currYDir() { return _wPul; }
		bool isAttacking() { return _isAttacking; };
		void setIsAttacking(bool b) { _isAttacking = b; };
};