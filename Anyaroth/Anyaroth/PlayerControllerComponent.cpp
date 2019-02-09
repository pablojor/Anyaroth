#include "PlayerControllerComponent.h"
#include "GameComponent.h"


PlayerControllerComponent::PlayerControllerComponent(GameComponent* obj) : InputComponent(obj) 
{
	_movement = obj->getComponent<MovingComponent>();
	if (_movement == nullptr) _movement = obj->addComponent<MovingComponent>();
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
		movement->changeDir(0, 0); //Llamo a animacion iddle
		//anim->playAnim("Idle");
	}
	else if (aPul)
	{
		movement->changeDir(-1, 0); //Llamo a animacion de moverse y un flip
		//anim->playAnim("Walk");
		//anim->flip();
	}
	else if (dPul)
	{
		movement->changeDir(1, 0); //Llamo a animacion de moverse
		//anim->playAnim("Walk");
		//anim->unFlip();
	}
	else
	{
		movement->changeDir(0, 0); //Llamo a animacion iddle
		//anim->playAnim("Idle");
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