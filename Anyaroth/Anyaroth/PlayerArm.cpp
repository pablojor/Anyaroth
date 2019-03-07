#include "PlayerArm.h"
#include "ArmControllerComponent.h"
#include "Gun.h"
#include "Player.h"

PlayerArm::PlayerArm(Texture* texture, Player* player, Game* g, PlayState* play, Vector2D offset) : Arm(texture, player, g, play, offset)
{
	_controller = addComponent<ArmControllerComponent>();
}

void PlayerArm::update()
{
	GameComponent::update();

	Vector2D mousePos = _cursor->getComponent<TransformComponent>()->getPosition();
	Vector2D mouseDim = { double(_cursor->getComponent<AnimatedSpriteComponent>()->getTexture()->getW()), double(_cursor->getComponent<AnimatedSpriteComponent>()->getTexture()->getH()) };

	//------------Rotacion del brazo
	rotate(Vector2D(mousePos.getX() + mouseDim.getX()/2, mousePos.getY() + mouseDim.getY() / 2));

	if ((static_cast<Player*>(_owner))->getCurrentState() == Player::Attacking ||
		(static_cast<Player*>(_owner))->getCurrentState() == Player::Reloading ||
		(static_cast<Player*>(_owner))->getCurrentState() == Player::Dashing)
		_anim->setActive(false);
	else
		_anim->setActive(true);


	if (_anim->animationFinished())
		_anim->playAnim(AnimatedSpriteComponent::Idle);
}

//Dispara el arma
void PlayerArm::shoot()
{
	if (_currentGun != nullptr)
	{
		double armAngle = _transform->getRotation(), armX = _transform->getPosition().getX(), armY = _transform->getPosition().getY();
    
		//----------Posicion inicial de la bala
		int posOffsetX = 24, posOffsetY = -1;

		Vector2D bulletPosition = { armX + (_anim->isFlipped() ? -posOffsetX : posOffsetX), armY + posOffsetY };
		bulletPosition = bulletPosition.rotateAroundPoint(armAngle, { armX, armY });

		//----------Direccion de la bala

		//Distincion flip-unflip
		int bulletDirOffset = 90;

		double aimAuxY = _anim->isFlipped() ? 1 : -1;
		Vector2D bulletDir = (Vector2D(0, aimAuxY).rotate(armAngle + bulletDirOffset));
		bulletDir.normalize();

		if(_currentGun->shoot(bulletPosition, bulletDir, _anim->isFlipped()))
			_anim->playAnim(AnimatedSpriteComponent::Shoot);
		else
		{
			if (_currentGun->getAmmo() > 0)
				static_cast<Player*>(_owner)->reload();
			else
				_anim->playAnim(AnimatedSpriteComponent::NoAmmo);
		}
	}
}

//Recarga el arma
bool PlayerArm::reload()
{
	return _currentGun->reload();	
}

void PlayerArm::setCursor(Cursor* c)
{
	_cursor = c;
	_controller->setCursorTC(c);
}