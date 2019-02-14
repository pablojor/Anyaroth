#include "ArmControllerComponent.h"
#include "GameComponent.h"
#include <cmath>
#include <iostream>

#define PI 3.14159265

ArmControllerComponent::ArmControllerComponent(GameComponent* obj) : InputComponent(obj)
{
	_transform = obj->getComponent<TransformComponent>();
	if (_transform == nullptr)
		_transform = obj->addComponent<TransformComponent>();

	_anim = obj->getComponent<AnimatedSpriteComponent>();
	if (_anim == nullptr)
		_anim = obj->addComponent<AnimatedSpriteComponent>();

	_followC = obj->getComponent<FollowingComponent>();
	_player = _followC->getOther();

	_minAimDistance = 100;
}

void ArmControllerComponent::handleInput(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEMOTION)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);


		Vector2D direction = { (_transform->getPosition().getX() + _followC->getInitialOffset().getX() - (x)),
			(_transform->getPosition().getY() + _followC->getInitialOffset().getY() - y) };

		if (!_anim->isFlipped())
		{
			//direction = direction + Vector2D(42, 0);


			if (x < _transform->getPosition().getX()) { //hago flip si el mouse está a la izquierda
				_anim->flip();
				_player->getComponent<AnimatedSpriteComponent>()->flip();
				_transform->setAnchor(1 - _transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
				//_transform->setPosition(0, 0);//_transform->getPosition().getX() - 40, _transform->getPosition().getY());
				_followC->setOffset({ _followC->getInitialOffset().getX() - _followC->getInitialOffset().getX(), _followC->getInitialOffset().getY() });
			}

		}
		else if (_anim->isFlipped())
		{
			//direction = direction + Vector2D(42, 0);

			if (x > _transform->getPosition().getX() + _followC->getInitialOffset().getX()) {
				_anim->unFlip();
				_player->getComponent<AnimatedSpriteComponent>()->unFlip();
				_transform->setAnchor(_transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
				//_transform->setPosition(_transform->getPosition().getX() + 40, _transform->getPosition().getY());
				_followC->setOffset({ _followC->getInitialOffset().getX(), _followC->getInitialOffset().getY() });
			}
		}

		//cout << (_transform->getPosition().getX()) << endl;

		



		direction.normalize();

		//Distancia del mouse al brazo
		double distance = sqrt(pow(x - _transform->getPosition().getX(), 2) + pow(y - _transform->getPosition().getY(), 2));
		cout << distance << endl;

		//actualizo angulo del brazo
		double rot = atan2(direction.getY(), direction.getX()) * 180.0 / PI;

		if (!_anim->isFlipped()) 
		{
			rot -= 180 - 10;
		}
		else
		{
			rot -= 10;
		}

		if (distance > _minAimDistance) {
			_transform->setRotation(rot);
			//_transform->setRotation(rot - pow(360/distance,2));
		}
	}


	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			_leftClickPul = true;
		}
	}

	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			_leftClickPul = false;
		}
	}

	if (_leftClickPul)
	{
		//llamo a función de disparar
	}
}