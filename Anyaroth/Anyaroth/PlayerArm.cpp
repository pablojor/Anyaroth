#include "PlayerArm.h"
#include "Player.h"
#include "Game.h"


PlayerArm::PlayerArm(Game* game, Player* player, Vector2D offset) : Arm(game, player, offset), _player(player)
{
	setTexture(game->getTexture("Arm"));
}

void PlayerArm::update(double deltaTime)
{
	GameObject::update(deltaTime);

	Vector2D mousePos;

	//Rotacion del brazo
	if (_player->isInputFreezed() || isReloading())
	{
		if (_player->getComponent<CustomAnimatedSpriteComponent>()->isFlipped())
			mousePos = { _transform->getPosition().getX() - 200, _transform->getPosition().getY() };
		else
			mousePos = { _transform->getPosition().getX() + 200, _transform->getPosition().getY() };
	}
	else
		mousePos = getGame()->getCurrentState()->getMousePositionInWorld();

	lookAtTarget(mousePos);
	handleFlipState(mousePos);



	if (reloadFinished())
	{
		_player->setIsReloading(false);
		_player->getPlayerPanel()->updateAmmoViewer(_player->getCurrentGun()->getClip(), _player->getCurrentGun()->getMagazine());
	}

	if (_anim->animationFinished())
		_anim->playAnim(AnimatedSpriteComponent::Idle);
}

//Activa animacion de disparo
void PlayerArm::shoot()
{
	if (_player->getCurrentGun()->canShoot())
		_anim->playAnim(AnimatedSpriteComponent::Shoot);
	else if (!_player->getCurrentGun()->canReload())
		_anim->playAnim(AnimatedSpriteComponent::NoAmmo);
}

//Activa animacion de recarga o de noAmmo
void PlayerArm::reload()
{
	//Activar animacion aqui
	_anim->playAnim(AnimatedSpriteComponent::Reload);
}

void PlayerArm::handleFlipState(const Vector2D& target)
{
	if (!_player->isDashing())
	{
		if (target.getX() < _transform->getPosition().getX())
		{
			_transform->setAnchor(1 - _transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
			_followC->setOffset({ _followC->getInitialOffset().getX() + 8 /*flipPosOffset*/, _followC->getInitialOffset().getY() });
			_transform->setRotation(_transform->getRotation() + 180);
			_anim->flip();
			_player->getComponent<CustomAnimatedSpriteComponent>()->flip();
		}
		else
		{
			_transform->setAnchor(_transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
			_followC->setOffset({ _followC->getInitialOffset().getX(), _followC->getInitialOffset().getY() });
			_anim->unFlip();
			_player->getComponent<CustomAnimatedSpriteComponent>()->unFlip();
		}
	}
}