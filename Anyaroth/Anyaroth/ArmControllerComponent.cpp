#include "ArmControllerComponent.h"
#include "GameComponent.h"
#include <cmath>
#include <iostream>
#include "Arm.h"

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

	_obj = obj;

	_minAimDistance = 32;
}

void ArmControllerComponent::handleInput(const SDL_Event& event)
{
	
		

	if (true)//(event.type == SDL_MOUSEMOTION)
	{
		int x, y;

		x = event.motion.x;
		y = event.motion.y;

		Vector2D direction = { (_transform->getPosition().getX() + _followC->getInitialOffset().getX() - (x)),
			(_transform->getPosition().getY() + _followC->getInitialOffset().getY() - y) };

		if (!_anim->isFlipped())
		{
			//direction = direction + Vector2D(42, 0);

			//cout << x << " " << _transform->getPosition().getX() << endl;
			if (x < _transform->getPosition().getX()) { //hago flip si el mouse está a la izquierda
				//cout << x << " " << _transform->getPosition().getX()<<endl;
				_anim->flip();
				_player->getComponent<AnimatedSpriteComponent>()->flip();
				_transform->setAnchor(1 - _transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
				_player->getComponent<TransformComponent>()->setPosition(_player->getComponent<TransformComponent>()->getPosition().getX() - magicNumber, _player->getComponent<TransformComponent>()->getPosition().getY());
				//_transform->setPosition(0, 0);//_transform->getPosition().getX() - 40, _transform->getPosition().getY());
				_followC->setOffset({ _followC->getInitialOffset().getX() + 18/*_followC->getInitialOffset().getX()*/, _followC->getInitialOffset().getY() });
			}

		}
		else if (_anim->isFlipped())
		{
			//direction = direction + Vector2D(42, 0);

			if (x > _transform->getPosition().getX() + _followC->getInitialOffset().getX()) {
				_anim->unFlip();
				_player->getComponent<AnimatedSpriteComponent>()->unFlip();
				_transform->setAnchor(_transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
				_player->getComponent<TransformComponent>()->setPosition(_player->getComponent<TransformComponent>()->getPosition().getX() + magicNumber, _player->getComponent<TransformComponent>()->getPosition().getY());
				//_transform->setPosition(_transform->getPosition().getX() + 40, _transform->getPosition().getY());
				_followC->setOffset({ _followC->getInitialOffset().getX(), _followC->getInitialOffset().getY() });
			}
		}

		//cout << (_transform->getPosition().getX()) << endl;





		direction.normalize();

		//Distancia del mouse al brazo
		double distance = sqrt(pow(x - _transform->getPosition().getX(), 2) + pow(y - _transform->getPosition().getY(), 2));

		//cout << distance << endl;

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

		if ((!_anim->isFlipped() && distance > _minAimDistance)
			|| _anim->isFlipped() && distance > _minAimDistance - 70) {
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
		(dynamic_cast<Arm*>(_obj))->shoot();   //llamo a función de disparar
	}
}