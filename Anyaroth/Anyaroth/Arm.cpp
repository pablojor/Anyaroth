#include "Arm.h"
#include "TransformComponent.h"
#include "Game.h"
#include "FollowingComponent.h"
#include "AnimatedSpriteComponent.h"
#include "ArmControllerComponent.h"
#include "Gun.h"

#define PI 3.14159265

Arm::Arm(Texture* texture, GameComponent* player, Game* g, Vector2D offset) : GameComponent(g)
{


	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();

	_anim = addComponent<AnimatedSpriteComponent>();

	if (player != nullptr)
	{
		setPlayer(offset, player);
	}



	_anim->addAnim(AnimatedSpriteComponent::None, 1, false);
	_anim->addAnim(AnimatedSpriteComponent::Shoot, 2, false);
	_anim->addAnim(AnimatedSpriteComponent::NoAmmo, 2, false);

	_anim->playAnim(AnimatedSpriteComponent::None);
	//anim->addAnim("Walk", 10);

	//_transform->setPosition(340, 100);

	//_transform->setDefaultAnchor(0.17, 0.3);
	_transform->setDefaultAnchor(0.1, 0.6); //Parámetros para la pistola
}


Arm::~Arm()
{
	delete _currentGun;
	_currentGun = nullptr;
}

void Arm::update()
{
	GameComponent::update();

	/*if (_currentGun != nullptr)
		_currentGun->debugInfo();
	else
		cout << "Gun Not found" << endl << endl;*/


		//------------Movimiento del brazo---------------------
	Vector2D direction = { (_transform->getPosition().getX() + _followC->getInitialOffset().getX() - (_controller->mouseX)),
			(_transform->getPosition().getY() + _followC->getInitialOffset().getY() - _controller->mouseY) };

	if (!_anim->isFlipped())
	{
		//direction = direction + Vector2D(42, 0);

		//cout << x << " " << _transform->getPosition().getX() << endl;
		if (_controller->mouseX < _transform->getPosition().getX()) { //hago flip si el mouse está a la izquierda
			//cout << x << " " << _transform->getPosition().getX()<<endl;
			_anim->flip();
			_player->getComponent<AnimatedSpriteComponent>()->flip();
			_transform->setAnchor(1 - _transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
			_player->getComponent<TransformComponent>()->setPosition(_player->getComponent<TransformComponent>()->getPosition().getX(), _player->getComponent<TransformComponent>()->getPosition().getY());
			//_transform->setPosition(0, 0);//_transform->getPosition().getX() - 40, _transform->getPosition().getY());
			_followC->setOffset({ _followC->getInitialOffset().getX()/* + 18/*_followC->getInitialOffset().getX()*/, _followC->getInitialOffset().getY() });
		}

	}
	else if (_anim->isFlipped())
	{
		//direction = direction + Vector2D(42, 0);

		if (_controller->mouseX > _transform->getPosition().getX() + _followC->getInitialOffset().getX()) {
			_anim->unFlip();
			_player->getComponent<AnimatedSpriteComponent>()->unFlip();
			_transform->setAnchor(_transform->getDefaultAnchor().getX(), _transform->getDefaultAnchor().getY());
			_player->getComponent<TransformComponent>()->setPosition(_player->getComponent<TransformComponent>()->getPosition().getX() + _magicNumber, _player->getComponent<TransformComponent>()->getPosition().getY());
			//_transform->setPosition(_transform->getPosition().getX() + 40, _transform->getPosition().getY());
			_followC->setOffset({ _followC->getInitialOffset().getX(), _followC->getInitialOffset().getY() });
		}
	}

	//cout << (_transform->getPosition().getX()) << endl;

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
		|| _anim->isFlipped() && distance > _minAimDistance - 20) {
		_transform->setRotation(rot);
		//_transform->setRotation(rot - pow(360/distance,2));
	}
	//-----------------------------------------------------------



	if ((static_cast<Player*>(_player))->getCurrentState() == Player::Attacking ||
		(static_cast<Player*>(_player))->getCurrentState() == Player::Reloading)
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
		if(_currentGun->shoot())
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