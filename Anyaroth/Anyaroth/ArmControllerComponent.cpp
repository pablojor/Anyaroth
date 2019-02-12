#include "ArmControllerComponent.h"
#include "GameComponent.h"
#include <math.h>

#define PI 3.14159265

ArmControllerComponent::ArmControllerComponent(GameComponent* obj) : InputComponent(obj)
{
	_transform = obj->getComponent<TransformComponent>();
	if (_transform == nullptr)
		_transform = obj->addComponent<TransformComponent>();

	_anim = obj->getComponent<AnimatedSpriteComponent>();
	if (_anim == nullptr)
		_anim = obj->addComponent<AnimatedSpriteComponent>();
}

void ArmControllerComponent::handleInput(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEMOTION)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		//actualizo angulo del brazo
		_transform->setRotation(atan((_transform->getPosition().getY()-y)/(x-_transform->getPosition().getX())) * 180 / PI);
	}


	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			_leftClickPul = true;
		}
		/*else if (event.button.button == SDL_BUTTON_RIGHT)
		{
			_rightClickPul = true;
		}*/
	}

	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			_leftClickPul = false;
		}
		/*else if (event.button.button == SDL_BUTTON_RIGHT)
		{
			_rightClickPul = true;
		}*/
	}

	if (_leftClickPul)
	{
		//llamo a función de disparar
	}


	/*if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_a)
			_aPul = true;
		else if (event.key.keysym.sym == SDLK_d)
			_dPul = true;

		if (event.key.keysym.sym == SDLK_w)
			_wPul = true;

		if (event.key.keysym.sym == SDLK_s)
			_sPul = true;

	}*/

	/*if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_a)
			_aPul = false;
		else if (event.key.keysym.sym == SDLK_d)
			_dPul = false;

		if (event.key.keysym.sym == SDLK_w)
			_wPul = false;

		if (event.key.keysym.sym == SDLK_s)
			_sPul = false;

	}*/
	
	/*if (_aPul == _dPul)
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
	}*/

}