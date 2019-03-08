#include "PlayerArm.h"
#include "ArmControllerComponent.h"
#include "Gun.h"



PlayerArm::PlayerArm(Texture* texture, GameComponent* player, Game* g, PlayState* play, Vector2D offset) : Arm(texture, player, g, play, offset)
{
	_controller = addComponent<ArmControllerComponent>();
	//_cursor = play->getCursor();
}

void PlayerArm::update()
{
		/*cout << "ARM_X: " << getComponent<TransformComponent>()->getPosition().getX() << "	ARM_Y: " << getComponent<TransformComponent>()->getPosition().getY() << endl << endl;*/
	

	GameComponent::update();

	Vector2D mousePos = _cursor->getComponent<TransformComponent>()->getPosition();
	Vector2D mouseDim = { double(_cursor->getComponent<AnimatedSpriteComponent>()->getTexture()->getW()), double(_cursor->getComponent<AnimatedSpriteComponent>()->getTexture()->getH()) };
	//------------Rotaci�n del brazo---------------------
	rotate(Vector2D(mousePos.getX() + mouseDim.getX()/2, mousePos.getY() + mouseDim.getY() / 2));
	//------------Comprueba si tiene que disparar--------
	if (_controller->isShooting())
	{
		shoot();//DISPARA
		if(!_currentGun->isAutomatic()) _controller->setShooting(false); //Si el arma no es automática, resetea el input de disparo
	}

	if ((static_cast<Player*>(_owner))->getCurrentState() == Player::Attacking ||
		(static_cast<Player*>(_owner))->getCurrentState() == Player::Reloading ||
		(static_cast<Player*>(_owner))->getCurrentState() == Player::Dashing)
	{
		_anim->setActive(false);
	}
	else
	{
		_anim->setActive(true);
	}


	if (_anim->animationFinished())
	{
		_anim->playAnim(AnimatedSpriteComponent::Idle);
	}
}

//Dispara el arma
void PlayerArm::shoot()
{
	if (_currentGun != nullptr && _currentGun->canShoot())
	{
		double armAngle = _transform->getRotation(),
			armX = _transform->getPosition().getX(),
			armY = _transform->getPosition().getY();
    
		//----------Posici�n inicial de la bala
		int posOffsetX = 24,
			posOffsetY = -1;

		Vector2D bulletPosition = { armX + (_anim->isFlipped() ? -posOffsetX : posOffsetX), armY + posOffsetY };
		bulletPosition = bulletPosition.rotateAroundPoint(armAngle, { armX, armY });


		//----------Direcci�n de la bala

		//Distinci�n flip-unflip
		int bulletDirOffset = 90;//_anim->isFlipped() ? 90 : 90;

		double aimAuxY = _anim->isFlipped() ? 1 : -1;
		Vector2D bulletDir = (Vector2D(0, aimAuxY).rotate(armAngle + bulletDirOffset));
		bulletDir.normalize();
		//bulletDir = bulletDir * 3;

		if(_currentGun->shoot(bulletPosition, bulletDir, _anim->isFlipped()))
		{
			_anim->playAnim(AnimatedSpriteComponent::Shoot);
		}
		else
		{
			if (_currentGun->getAmmo() > 0)
			{
				static_cast<Player*>(_owner)->reload();
			}
			else
			{
				_anim->playAnim(AnimatedSpriteComponent::NoAmmo);
			}
			
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