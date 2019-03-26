#include "ArmControllerComponent.h"
#include "GameComponent.h"
#include <cmath>
#include <iostream>
#include "PlayerArm.h"
#include "Player.h"

ArmControllerComponent::ArmControllerComponent(GameComponent* obj) : InputComponent(obj)
{
	_transform = obj->getComponent<TransformComponent>();
	_anim = obj->getComponent<AnimatedSpriteComponent>();
	_followC = obj->getComponent<FollowingComponent>();

	_player = _followC->getOther();
	_obj = dynamic_cast<PlayerArm*>(obj);
}

void ArmControllerComponent::handleInput(const SDL_Event& event)
{
	if (!_anim->isFlipped() && _cursorTC->getPosition().getX() < _transform->getPosition().getX())
	{
		_anim->flip();
		_player->getComponent<AnimatedSpriteComponent>()->flip();
		_transform->setAnchor(1 - _transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
		_followC->setOffset({ _followC->getInitialOffset().getX() + flipPosOffset, _followC->getInitialOffset().getY() });
	}
	else if (_anim->isFlipped() && _cursorTC->getPosition().getX() > _transform->getPosition().getX())
	{
		_anim->unFlip();
		_player->getComponent<AnimatedSpriteComponent>()->unFlip();
		_transform->setAnchor(_transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
		_followC->setOffset({ _followC->getInitialOffset().getX(), _followC->getInitialOffset().getY() });
	}

	if (_leftClickPul && _canShoot)
	{
		_obj->shoot();
		_canShoot = false;
	}
}