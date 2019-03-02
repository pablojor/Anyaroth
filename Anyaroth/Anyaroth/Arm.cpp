#include "Arm.h"
#include "PlayState.h"


Arm::Arm(Texture* texture, GameComponent* owner, Game* g, PlayState* play, Vector2D offset) : GameComponent(g)
{


	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();

	_anim = addComponent<AnimatedSpriteComponent>();

	if (owner != nullptr)
	{
		setOwner(offset, owner);
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
}

void Arm::setArmSprite(Texture* armTex)
{
	_anim->setTexture(armTex);
}

void Arm::setOwner(Vector2D offset, GameComponent* owner)
{
	_owner = owner;
	_followC = addComponent<FollowingComponent>(_owner);
	_followC->setInitialOffset(offset);
}