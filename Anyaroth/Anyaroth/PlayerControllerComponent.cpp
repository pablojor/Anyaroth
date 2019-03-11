#include "PlayerControllerComponent.h"
#include "GameComponent.h"
#include "Player.h"

PlayerControllerComponent::PlayerControllerComponent(GameComponent* obj) : InputComponent(obj)
{
	_movement = obj->getComponent<MovingComponent>();
	_anim = obj->getComponent<AnimatedSpriteComponent>();
	_obj = obj;
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
			_spacePul = true;

		if (event.key.keysym.sym == SDLK_s)
			_sPul = true;

		if (event.key.keysym.sym == SDLK_LSHIFT)
			_sfPul = true;

		if (event.key.keysym.sym == SDLK_r)
			_rPul = true;

		if (event.key.keysym.sym == SDLK_q)
			_qPul = true;
	}

	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_a)
			_aPul = false;
		else if (event.key.keysym.sym == SDLK_d)
			_dPul = false;

		if (event.key.keysym.sym == SDLK_SPACE)
			_spacePul = false;

		if (event.key.keysym.sym == SDLK_s)
			_sPul = false;

		if (event.key.keysym.sym == SDLK_LSHIFT)
			_sfPul = false;

		if (event.key.keysym.sym == SDLK_r)
			_rPul = false;

		if (event.key.keysym.sym == SDLK_q)
		{
			_qPul = false;
			_isSwapping = false;
		}
	}

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_RIGHT)
			_rightClickPul = true;
	}

	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_RIGHT)
			_rightClickPul = false;
	}

	_dashing = _movement->isDashing();

	if (_rightClickPul && !_dashing && !_isAttacking && !_jumping)
	{
		Player* player = static_cast<Player*>(_obj);
		_movement->changeDir(0, 0);
		_isAttacking = true;
		//llamo a funci�n de melee
		player->meleeAttack();
		player->setCurrentState(Player::Attacking);
		_anim->playAnim(AnimatedSpriteComponent::MeleeKnife);//llamo animacion del melee dependiendo del arma cuerpo a cuerpo
	}

	if ((_aPul &&_dPul) && !_isAttacking && !_dashing && !_isReloading)
	{
		_movement->changeDir(0, 0); //llamo a animacion idle
		_anim->playAnim(AnimatedSpriteComponent::Idle);
		static_cast<Player*>(_obj)->setCurrentState(Player::Idle);
	}
	else if (_aPul && !_isAttacking && !_dashing && !_isReloading)
	{
		_movement->changeDir(-1, 0); //llamo a animacion de moverse y un flip
		if (_sfPul && _amountOfDash > 0)
		{
			_movement->changeDash(true);
			_dashing = true;
			_amountOfDash--;

			if (!_anim->isFlipped())
				_anim->playAnim(AnimatedSpriteComponent::DashBack);
			else
				_anim->playAnim(AnimatedSpriteComponent::Dash);

			static_cast<Player*>(_obj)->setCurrentState(Player::Dashing);  ///// I HATE YOUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU (no borrar)

		}
		else if (!_jumping)
		{
			if (!_anim->isFlipped())
				_anim->playAnim(AnimatedSpriteComponent::WalkBack);
			else
				_anim->playAnim(AnimatedSpriteComponent::Walk);

			static_cast<Player*>(_obj)->setCurrentState(Player::Walking);
		}
	}
	else if (_dPul && !_isAttacking && !_dashing && !_isReloading)
	{
		_movement->changeDir(1, 0); //llamo a animacion de moverse
		if (_sfPul && _amountOfDash > 0)
		{
			_movement->changeDash(true);
			_dashing = true;
			_amountOfDash--;

			if (!_anim->isFlipped())
				_anim->playAnim(AnimatedSpriteComponent::Dash);
			else
				_anim->playAnim(AnimatedSpriteComponent::DashBack);

			static_cast<Player*>(_obj)->setCurrentState(Player::Dashing);
		}
		else if (!_jumping)
		{
			if (!_anim->isFlipped())
				_anim->playAnim(AnimatedSpriteComponent::Walk);
			else
				_anim->playAnim(AnimatedSpriteComponent::WalkBack);

			static_cast<Player*>(_obj)->setCurrentState(Player::Walking);
		}
	}
	else if (_sPul && _sfPul && !_isAttacking && _jumping && !_dashing && _amountOfDash > 0 && !_isReloading)
	{
		_movement->changeDir(0, 1);
		_movement->changeDash(true);
		_dashing = true;
		_amountOfDash--;
		_anim->playAnim(AnimatedSpriteComponent::DashDown);
		static_cast<Player*>(_obj)->setCurrentState(Player::Dashing);
		//llamo a componente de dash hacia abajo (culo)
	}
	else if (!_isAttacking && !_dashing && !_isReloading)
	{
		_movement->changeDir(0, 0); //llamo a animacion idle
		if (!_jumping)
			_anim->playAnim(AnimatedSpriteComponent::Idle);
	}

	if (_spacePul && !_isAttacking && !_jumping && !_dashing && !_isReloading)
	{
		_movement->changeDir(_movement->getDirX(), -1);
		_anim->playAnim(AnimatedSpriteComponent::BeforeJump);
	}
	if (_rPul && !_dashing)
	{
		if (static_cast<Player*>(_obj)->getWeaponArm()->reload()) //llamo a función de recargar
			reload();
	}
	if (_qPul && !_isSwapping && !_dashing)
	{
		_isSwapping = true;
		static_cast<Player*>(_obj)->swapGun();
		_qPul = false;
	}
}

void PlayerControllerComponent::changeJump()
{
	_jumping = true;

	if (!_dashing)
	{
		_movement->changeDir(_movement->getDirX(), 0);

		if (static_cast<Player*>(_obj)->getCurrentState() == Player::Falling)
		{
			if (_anim->animationFinished())
				_anim->playAnim(AnimatedSpriteComponent::Falling);
		}
		else if (static_cast<Player*>(_obj)->getCurrentState() == Player::Jumping)
			_anim->playAnim(AnimatedSpriteComponent::Jump);
	}
}

void PlayerControllerComponent::ableJump()
{
	if (_jumping)
	{
		_dashing = false;
		_movement->changeDash(false);
	}

	_jumping = false;

	if (_anim->getCurrentAnim() == AnimatedSpriteComponent::Falling || _anim->getCurrentAnim() == AnimatedSpriteComponent::Jump ||
		_anim->getCurrentAnim() == AnimatedSpriteComponent::StartFalling || _anim->getCurrentAnim() == AnimatedSpriteComponent::DashDown)
	{
		if (_movement->getDirX() == 0)
		{
			static_cast<Player*>(_obj)->setCurrentState(Player::Idle);
			_anim->playAnim(AnimatedSpriteComponent::Idle);
		}
		else
		{
			static_cast<Player*>(_obj)->setCurrentState(Player::Walking);

			if (!_anim->isFlipped())
				_anim->playAnim(AnimatedSpriteComponent::Walk);
			else
				_anim->playAnim(AnimatedSpriteComponent::WalkBack);
		}
	}
}

void PlayerControllerComponent::reload()
{
	_movement->changeDir(0, 0);
	_isReloading = true;
	static_cast<Player*>(_obj)->setCurrentState(Player::Reloading);

	switch (static_cast<Player*>(_obj)->getWeaponArm()->getCurrentGun()->getType())
	{
	case GunType::BasicGun:
		_anim->playAnim(AnimatedSpriteComponent::ReloadPistol); //llamo animacion de recargar
		break;
	case GunType::BasicShotgun:
		_anim->playAnim(AnimatedSpriteComponent::ReloadShotgun);
		break;
	default:
		break;
	}
}