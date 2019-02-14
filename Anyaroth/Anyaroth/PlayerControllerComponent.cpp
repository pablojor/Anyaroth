#include "PlayerControllerComponent.h"
#include "GameComponent.h"


PlayerControllerComponent::PlayerControllerComponent(GameComponent* obj) : InputComponent(obj) 
{
	_movement = obj->getComponent<MovingComponent>();
	if (_movement == nullptr) 
		_movement = obj->addComponent<MovingComponent>();

	_anim = obj->getComponent<AnimatedSpriteComponent>();
	if (_anim == nullptr) 
		_anim = obj->addComponent<AnimatedSpriteComponent>();
}

void PlayerControllerComponent::handleInput(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_a)
			_aPul = true;
		else if (event.key.keysym.sym == SDLK_d)
			_dPul = true;

		if (event.key.keysym.sym == SDLK_w)
			_wPul = true;

		if (event.key.keysym.sym == SDLK_s)
			_sPul = true;
	}

	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_a)
			_aPul = false;
		else if (event.key.keysym.sym == SDLK_d)
			_dPul = false;

		if (event.key.keysym.sym == SDLK_w)
			_wPul = false;

		if (event.key.keysym.sym == SDLK_s)
			_sPul = false;
	}

	if (_aPul == _dPul)
	{
		_movement->changeDir(0, 0); //Llamo a animacion iddle
		_anim->playAnim("Idle");
	}
	else if (_aPul)
	{
		_movement->changeDir(-1, 0); //Llamo a animacion de moverse y un flip
		_anim->playAnim("Walk");
		_anim->flip();
	}
	else if (_dPul)
	{
		_movement->changeDir(1, 0); //Llamo a animacion de moverse
		_anim->playAnim("Walk");
		_anim->unFlip();
	}
	else
	{
		_movement->changeDir(0, 0); //Llamo a animacion iddle
		_anim->playAnim("Idle");
	}

	if (_wPul /*Y no estoy saltando ya*/)
	{
		_movement->changeDir(_movement->getDirX(), -1);
	}
}