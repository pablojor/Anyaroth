#include "Arm.h"
#include "TransformComponent.h"
#include "Game.h"
#include "FollowingComponent.h"
#include "AnimatedSpriteComponent.h"
#include "ArmControllerComponent.h"
#include "Gun.h"
#include "PlayState.h"
#include "Camera.h"

#define PI 3.14159265

Arm::Arm(Texture* texture, GameComponent* player, Game* g, PlayState* play, Vector2D offset) : GameComponent(g)
{


	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();

	_anim = addComponent<AnimatedSpriteComponent>();

	if (player != nullptr)
	{
		setPlayer(offset, player);
	}

	_cam = play->getMainCamera();

	_anim->addAnim(AnimatedSpriteComponent::None, 1, false);
	_anim->addAnim(AnimatedSpriteComponent::Shoot, 2, false);
	_anim->addAnim(AnimatedSpriteComponent::NoAmmo, 2, false);

	_anim->playAnim(AnimatedSpriteComponent::None);
	//anim->addAnim("Walk", 10);

	//_transform->setPosition(340, 100);

	//_transform->setDefaultAnchor(0.17, 0.3);
	_transform->setDefaultAnchor(0.1, 0.6); //Par�metros para la pistola
}

Arm::~Arm()
{
	delete _currentGun;
	_currentGun = nullptr;
}

void Arm::update()
{
		/*cout << "ARM_X: " << getComponent<TransformComponent>()->getPosition().getX() << "	ARM_Y: " << getComponent<TransformComponent>()->getPosition().getY() << endl << endl;*/
	

	GameComponent::update();

		//------------Rotaci�n del brazo---------------------
	Vector2D direction = { (_transform->getPosition().getX() + _followC->getInitialOffset().getX() - (_controller->mouseX)),
			(_transform->getPosition().getY() + _followC->getInitialOffset().getY() - _controller->mouseY) };

	direction.normalize();

	//Distancia del mouse al brazo
	double distance = sqrt(pow(_controller->mouseX - _transform->getPosition().getX(), 2) + pow(_controller->mouseY - _transform->getPosition().getY(), 2));

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
		|| _anim->isFlipped() && distance > _minAimDistance + _controller->flipPosOffset) {
		_transform->setRotation(rot);
		//_transform->setRotation(rot - pow(360/distance,2));
	}
	//-----------------------------------------------------------



	if ((static_cast<Player*>(_player))->getCurrentState() == Player::Attacking ||
		(static_cast<Player*>(_player))->getCurrentState() == Player::Reloading ||
		(static_cast<Player*>(_player))->getCurrentState() == Player::Dashing)
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

void Arm::setPlayer(Vector2D offset, GameComponent* player)
{
	_player = player;
	_followC = addComponent<FollowingComponent>(_player);
	_followC->setInitialOffset(offset);
	_controller = addComponent<ArmControllerComponent>();
}

//Dispara el arma
void Arm::shoot()
{
	if (_currentGun != nullptr)
	{
		//----------Posici�n inicial de la bala

		//Distinci�n flip-unflip
		int bulletXOffset = _anim->isFlipped() ? -18 : -20;
		int bulletYOffset = _anim->isFlipped() ? -16 : -6;
		double aimAuxY = _anim->isFlipped() ? 1 : -1;

		Vector2D bulletPosition =
		{
			_transform->getPosition().getX() + bulletXOffset + _anim->getTexture()->getW() / 4,
			_transform->getPosition().getY() + _anim->getTexture()->getH() / 5 + bulletYOffset
		};
		
		Vector2D aux = (Vector2D(0, aimAuxY).rotate(_transform->getRotation() + 80))*(_anim->getTexture()->getH() / 2);

		bulletPosition = bulletPosition + aux;


		//----------Direcci�n de la bala

		//Distinci�n flip-unflip
		int bulletDirOffset = _anim->isFlipped() ? 95 : 90;

		Vector2D bulletDir = (Vector2D(0, aimAuxY).rotate(_transform->getRotation() + bulletDirOffset));
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
				static_cast<Player*>(_player)->reload();
			}
			else
			{
				_anim->playAnim(AnimatedSpriteComponent::NoAmmo);
			}
			
		}
	}
	else
		cout << "Gun Not found" << endl;

}

//Recarga el arma
bool Arm::reload()
{
	return _currentGun->reload();
	
}

void Arm::setGun(Gun* gun)
{
	if (_currentGun != nullptr) //Si ya hay un arma, llama a su destructora
		delete _currentGun;

	_currentGun = gun;
}