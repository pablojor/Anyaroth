#include "PlayerControllerComponent.h"
#include "GameComponent.h"
#include "Player.h"

PlayerControllerComponent::PlayerControllerComponent(GameComponent* obj) : InputComponent(obj)
{
	_movement = obj->getComponent<MovingComponent>();
	if (_movement == nullptr)
		_movement = obj->addComponent<MovingComponent>();

	_anim = obj->getComponent<AnimatedSpriteComponent>();
	if (_anim == nullptr)
		_anim = obj->addComponent<AnimatedSpriteComponent>();

	_obj = obj;
	jumping = false;
}

void PlayerControllerComponent::handleInput(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_a)
			_aPul = true;
		else if (event.key.keysym.sym == SDLK_d)
			_dPul = true;

		if (event.key.keysym.sym == SDLK_SPACE)
			_wPul = true;

		if (event.key.keysym.sym == SDLK_s)
			_sPul = true;
		if (event.key.keysym.sym == SDLK_LSHIFT)
			_sfPul = true;
	}

	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_a)
			_aPul = false;
		else if (event.key.keysym.sym == SDLK_d)
			_dPul = false;

		if (event.key.keysym.sym == SDLK_SPACE)
			_wPul = false;

		if (event.key.keysym.sym == SDLK_s)
			_sPul = false;
		if (event.key.keysym.sym == SDLK_LSHIFT)
			_sfPul = false;
	}

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_RIGHT)
		{
			_rightClickPul = true;
		}
	}

	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_RIGHT) //&& _isAttacking)
		{
			_rightClickPul = false;
		}
	}

	if (_rightClickPul && !dashing) //&& !_isAttacking)
	{
		_movement->changeDir(0, 0);
		_isAttacking = true;
		//llamo a funci�n de melee
		dynamic_cast<Player*>(_obj)->setCurrentState(Player::Attacking);
		//_animArm->setActive(false);//desactivo brazo
		_anim->playAnim(AnimatedSpriteComponent::MeleeKnife);//llamo animacion del melee dependiendo del arma cuerpo a cuerpo
	}

	

	if ((_aPul &&_dPul ) && !_isAttacking&&!dashing)
	{
		_movement->changeDir(0, 0); //Llamo a animacion idle
		_anim->playAnim(AnimatedSpriteComponent::Idle);
	}
	else if (_aPul && !_isAttacking&&!_wallOnL && !dashing)
	{
		_movement->changeDir(-1, 0); //Llamo a animacion de moverse y un flip
		if (_sfPul)
		{
			_movement->changeDash(true);
			dashing = true;
		}
		else 
		{
			if (!_anim->isFlipped())
				_anim->playAnim(AnimatedSpriteComponent::WalkBack);
			else
				_anim->playAnim(AnimatedSpriteComponent::Walk);
		}

		
	}
	else if (_dPul && !_isAttacking&&!_wallOnR && !dashing)
	{
		_movement->changeDir(1, 0); //Llamo a animacion de moverse
		if (_sfPul)
		{
			_movement->changeDash(true);
			dashing = true;
		}
		else 
		{
			if (!_anim->isFlipped())
				_anim->playAnim(AnimatedSpriteComponent::Walk);
			else
				_anim->playAnim(AnimatedSpriteComponent::WalkBack);
		}

	}
	else if (_sPul && _sfPul && !_isAttacking && jumping && !dashing)
	{
		_movement->changeDir(0, 1);
		_movement->changeDash(true);
		dashing = true;
		//Llamo a componente de dash hacia abajo (culo)
	}
	else if (!_isAttacking &&!dashing)
	{
		_movement->changeDir(0, 0); //Llamo a animacion idle
		_anim->playAnim(AnimatedSpriteComponent::Idle);
		
	}
	
	if (_wPul && !_isAttacking && !jumping&&!dashing)
	{
		_movement->changeDir(_movement->getDirX(), -1);
		jump = false;
	}
	
	
	//if (_sPul && _sfPul && jumping&& !dashing)
	//{
	//	_movement->changeDir(0, 1);
	//	_movement->changeDash(true);
	//	dashing = true;
	//	//Llamo a componente de dash hacia abajo (culo)
	//}
}

void PlayerControllerComponent::changeJump()
{
	
		jumping = true;
		if(!dashing)
		_movement->changeDir(_movement->getDirX(), 0);
		


	
	
}

void PlayerControllerComponent::ableJump()
{
	jump = true;
	if (jumping)
	{
		dashing = false;
		_movement->changeDash(false);
	}
	jumping = false;
	
}

void PlayerControllerComponent::wallOnLeft(bool yes)
{
	_wallOnL = yes;
	if (yes)
	{
		dashing = false;
		_movement->changeDash(false);
		_movement->changeDir(0, 0);
	}
}

void PlayerControllerComponent::wallOnRight(bool yes)
{
	_wallOnR = yes;
	if (yes)
	{
		dashing = false;
		_movement->changeDash(false);
		_movement->changeDir(0, 0);
	}
}
