#include "Arm.h"
#include "TransformComponent.h"
#include "Game.h"
#include "FollowingComponent.h"
#include "AnimatedSpriteComponent.h"
#include "ArmControllerComponent.h"
#include "Gun.h"

Arm::Arm(Texture* texture, GameComponent* player, Game* g, Vector2D offset) : GameComponent(g)
{


	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();

	_anim = addComponent<AnimatedSpriteComponent>();

	if (player != nullptr)
	{
		setPlayer(offset, player);
	}



	_anim->addAnim(AnimatedSpriteComponent::Idle, 1, false);

	_anim->playAnim(AnimatedSpriteComponent::Idle);
	//anim->addAnim("Walk", 10);

	//_transform->setPosition(340, 100);
	_transform->setDefaultAnchor(0.17, 0.3);

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

	if ((dynamic_cast<Player*>(_player))->getCurrentState() == Player::Attacking)
	{
		_anim->setActive(false);
	}
	else
	{
		_anim->setActive(true);
	}
}

void Arm::setPlayer(Vector2D offset, GameComponent* player)
{
	_player = player;
	auto fC = addComponent<FollowingComponent>(_player);
	fC->setInitialOffset(offset);
	addComponent<ArmControllerComponent>();
}

//Dispara el arma
void Arm::shoot()
{
	if (_currentGun != nullptr)
		_currentGun->shoot();
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