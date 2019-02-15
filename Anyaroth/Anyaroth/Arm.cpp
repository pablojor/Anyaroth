#include "Arm.h"
#include "TransformComponent.h"
#include "Game.h"
#include "FollowingComponent.h"
#include "AnimatedSpriteComponent.h"
#include "ArmControllerComponent.h"
//#include "PlayerControllerComponent.h"

Arm::Arm(Texture* texture, GameComponent* player, Vector2D offset) : GameComponent()
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

	_transform->setScale(RESOLUTION); //el 3 sería el factor de resolución!!
	//_transform->setPosition(340, 100);
	_transform->setDefaultAnchor(0.17, 0.3);

}


Arm::~Arm()
{

}

void Arm::update()
{
	GameComponent::update();

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
