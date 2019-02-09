#include "PlayerControllerComponent.h"
#include "GameComponent.h"


PlayerControllerComponent::PlayerControllerComponent(GameComponent* obj) : InputComponent(obj) 
{
	_movement = obj->getComponent<MovingComponent>();
	if (_movement == nullptr) _movement = obj->addComponent<MovingComponent>();
	_anim = obj->getComponent<AnimatedSpriteComponent>();
	if (_anim == nullptr) _anim = obj->addComponent<AnimatedSpriteComponent>();
}

void PlayerControllerComponent::handleInput(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_a)
			aPul = true;
		else if (event.key.keysym.sym == SDLK_d)
			dPul = true;

		if (event.key.keysym.sym == SDLK_w)
			wPul = true;

		if (event.key.keysym.sym == SDLK_s)
			sPul = true;

	}

	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_a)
			aPul = false;
		else if (event.key.keysym.sym == SDLK_d)
			dPul = false;

		if (event.key.keysym.sym == SDLK_w)
			wPul = false;

		if (event.key.keysym.sym == SDLK_s)
			sPul = false;

	}

	if (aPul == dPul)
	{
		_movement->changeDir(0, 0); //Llamo a animacion iddle
		_anim->playAnim("Idle");
	}
	else if (aPul)
	{
		_movement->changeDir(-1, 0); //Llamo a animacion de moverse y un flip
		_anim->playAnim("Walk");
		_anim->flip();
	}
	else if (dPul)
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

	if (wPul /*Y no estoy saltando ya*/)
	{
		//Llamo a compoennte de salto
	}

	if (sPul)
	{
		//Llamo a compoennte de agacharse
	}
}