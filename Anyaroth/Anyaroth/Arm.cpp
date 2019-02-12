#include "Arm.h"
#include "TransformComponent.h"
#include "Game.h"
#include "FollowingComponent.h"
#include "AnimatedSpriteComponent.h"
#include "ArmControllerComponent.h"

Arm::Arm(Texture* texture, GameComponent* player) : GameComponent()
{
	_player = player;

	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();

	_anim = addComponent<AnimatedSpriteComponent>();

	addComponent<FollowingComponent>(_player);

	addComponent<ArmControllerComponent>();


	_anim->addAnim("Idle", 1);

	_anim->playAnim("Idle");
	//anim->addAnim("Walk", 10);

	_transform->setScale(RESOLUTION); //el 3 sería el factor de resolución!!
	_transform->setPosition(340, 100);
	_transform->setAnchor(0, 0);
}


Arm::~Arm()
{

}

void Arm::update()
{
	GameComponent::update();

	if (_player->getComponent<AnimatedSpriteComponent>()->isFlipped() && !_anim->isFlipped())
	{
		_anim->flip();
	}
	else if(_anim->isFlipped())
	{
		_anim->unFlip();
	}
}
