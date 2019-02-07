#include "PlayerControllerComponent.h"


void PlayerControllerComponent::handleInput(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_a)
			aPul = true;
		else if (event.key.keysym.sym == SDLK_d)
			dPul = true;

		if(event.key.keysym.sym == SDLK_w)
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
		movement->changeDir(0, 0); //Llamo a animacion iddle
	else if (aPul)
		movement->changeDir(-1, 0); //Llamo a animacion de moverse y un flip
	else if (dPul)
		movement->changeDir(1, 0); //Llamo a animacion de moverse
	else
		movement->changeDir(0, 0); //Llamo a animacion iddle

	if (wPul /*Y no estoy saltando ya*/)
	{
		//Llamo a compoennte de salto
	}

	if (sPul)
	{
		//Llamo a compoennte de agacharse
	}
}