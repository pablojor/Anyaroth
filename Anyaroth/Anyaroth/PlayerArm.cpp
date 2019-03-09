#include "PlayerArm.h"
#include "Player.h"
#include "Game.h"


PlayerArm::PlayerArm(Game* g, Player* player, Vector2D offset) : Arm(g, player, offset) ,_player(player)
{
	setTexture(g->getTexture("Arm"));
}

void PlayerArm::update()
{
	GameComponent::update();

	/*if ((static_cast<Player*>(_owner))->getCurrentState() == Player::Attacking ||
		(static_cast<Player*>(_owner))->getCurrentState() == Player::Reloading ||
		(static_cast<Player*>(_owner))->getCurrentState() == Player::Dashing)
		_anim->setActive(false);
	else
		_anim->setActive(true);*/	

	//------------Rotacion del brazo
	Vector2D mousePos = getGame()->getCurrentState()->getMousePositionInWorld(); 
	lookAtTarget(mousePos);
	handleFlipState(mousePos);

	if (_anim->animationFinished())
		_anim->playAnim(AnimatedSpriteComponent::Idle);
}

//Dispara el arma
void PlayerArm::shoot()
{
	//Activar animacion aqui

	/*Arm::shoot();
	if (_currentGun != nullptr)
	{
		if(_currentGun->shoot(bulletPosition, bulletDir, _anim->isFlipped()))
			_anim->playAnim(AnimatedSpriteComponent::Shoot);
		else
		{
			if (_currentGun->getAmmo() > 0)
				_player->reload();
			else
				_anim->playAnim(AnimatedSpriteComponent::NoAmmo);
		}
	}*/
}

//Recarga el arma
bool PlayerArm::reload()
{
	//Activar animacion aqui

	return _currentGun->reload();	
}


void PlayerArm::handleFlipState(const Vector2D& target)
{
	if (target.getX() < _transform->getPosition().getX())
	{
		_transform->setAnchor(1 - _transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
		_followC->setOffset({ _followC->getInitialOffset().getX() + 8 /*flipPosOffset*/, _followC->getInitialOffset().getY() });
		_transform->setRotation(_transform->getRotation() + 180);
		_anim->flip();
		_player->getComponent<AnimatedSpriteComponent>()->flip();
	}
	else
	{
		_transform->setAnchor(_transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
		_followC->setOffset({ _followC->getInitialOffset().getX(), _followC->getInitialOffset().getY() });
		_anim->unFlip();
		_player->getComponent<AnimatedSpriteComponent>()->unFlip();
	}
}