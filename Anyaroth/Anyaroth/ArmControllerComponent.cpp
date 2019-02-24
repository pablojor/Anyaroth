#include "ArmControllerComponent.h"
#include "GameComponent.h"
#include <cmath>
#include <iostream>
#include "Arm.h"

//#define PI 3.14159265

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
}

void ArmControllerComponent::handleInput(const SDL_Event& event)
{
	//si se mueve el raton, se actualiza
	if (event.type == SDL_MOUSEMOTION)
	{
  		mouseX = event.motion.x;
		mouseY = event.motion.y;
	}

	//------------Flip del brazo---------------------
	if (!_anim->isFlipped() && mouseX < _transform->getPosition().getX())
	{
		_anim->flip();
		_player->getComponent<AnimatedSpriteComponent>()->flip();
		_transform->setAnchor(1 - _transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
		//_player->getComponent<TransformComponent>()->setPosition(_player->getComponent<TransformComponent>()->getPosition().getX(), _player->getComponent<TransformComponent>()->getPosition().getY());
		//_transform->setPosition (_transform->getPosition().getX() - 40, _transform->getPosition().getY());
		_followC->setOffset({ _followC->getInitialOffset().getX() - 14/*_followC->getInitialOffset().getX()*/, _followC->getInitialOffset().getY() });
		//cout << _followC->getOffset().getX() << endl;
	}
	else if (_anim->isFlipped() && mouseX > _transform->getPosition().getX() + _followC->getInitialOffset().getX())
	{
		_anim->unFlip();
		_player->getComponent<AnimatedSpriteComponent>()->unFlip();
		_transform->setAnchor(_transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
		//_player->getComponent<TransformComponent>()->setPosition(_player->getComponent<TransformComponent>()->getPosition().getX() + _magicNumber, _player->getComponent<TransformComponent>()->getPosition().getY());
		//_transform->setPosition(_transform->getPosition().getX() + 40, _transform->getPosition().getY());
		_followC->setOffset({ _followC->getInitialOffset().getX(), _followC->getInitialOffset().getY() });
		//cout << _followC->getOffset().getX() << endl;
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
			_canShoot = true;
		}
	}

	if (_leftClickPul && _canShoot)
	{
		(dynamic_cast<Arm*>(_obj))->shoot();   //llamo a función de disparar
		_canShoot = false;
	}

}