#include "ArmControllerComponent.h"
#include "GameComponent.h"
#include <cmath>
#include <iostream>
#include "PlayerArm.h"

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

	_obj = dynamic_cast<PlayerArm*>(obj);
	
}

void ArmControllerComponent::handleInput(const SDL_Event& event)
{
	


	//------------Flip del brazo---------------------
	if (!_anim->isFlipped() && _cursorTC->getPosition().getX() < _transform->getPosition().getX())
	{
		_anim->flip();
		_player->getComponent<AnimatedSpriteComponent>()->flip();
		_transform->setAnchor(1 - _transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
		_followC->setOffset({ _followC->getInitialOffset().getX() + flipPosOffset, _followC->getInitialOffset().getY() });
		
		if (event.type == SDL_MOUSEBUTTONDOWN)
			_flipShot = true;
	}
	else if (_anim->isFlipped() && (_cursorTC->getPosition().getX() > _transform->getPosition().getX() || (_transform->getRotation() >= 90 || _transform->getRotation() <= -90)))
	{
		_anim->unFlip();
		_player->getComponent<AnimatedSpriteComponent>()->unFlip();
		_transform->setAnchor(_transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
		_followC->setOffset({ _followC->getInitialOffset().getX(), _followC->getInitialOffset().getY() });

		if (event.type == SDL_MOUSEBUTTONDOWN)
			_flipShot = true;
	}
	else if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			_leftClickPul = true;
		}
	}
	

	/*if (!_anim->isFlipped() && ((_transform->getRotation() <= -90 && _transform->getRotation() > -300 || _transform->getRotation() >= -270 && _transform->getRotation() && _transform->getRotation() < -300)))
	{
		_anim->flip();
		_player->getComponent<AnimatedSpriteComponent>()->flip();
		_transform->setAnchor(1 - _transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
		_followC->setOffset({ _followC->getInitialOffset().getX() + flipPosOffset, _followC->getInitialOffset().getY() });
	}
	else if (_anim->isFlipped() && (_transform->getRotation() >= 90 || _transform->getRotation() <= -90))
	{
		_anim->unFlip();
		_player->getComponent<AnimatedSpriteComponent>()->unFlip();
		_transform->setAnchor(_transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
		_followC->setOffset({ _followC->getInitialOffset().getX(), _followC->getInitialOffset().getY() });
	}*/

	

	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			_leftClickPul = false;
			_canShoot = true;
		}
	}

	/*if (_leftClickPul && _canShoot)
	{
		_obj->shoot();   //llamo a funci�n de disparar
		_canShoot = false;
	}*/
}