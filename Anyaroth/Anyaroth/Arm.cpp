#include "Arm.h"
#include "Game.h"
#include <math.h>

Arm::Arm(Game* g, GameObject* owner, Vector2D offset) : GameObject(g), _owner(owner)
{
	addComponent<Texture>(g->getTexture("Arm"));
	_transform = addComponent<TransformComponent>();
	_anim = addComponent<CustomAnimatedSpriteComponent>();

	_followC = addComponent<FollowingComponent>(_owner);
	_followC->setInitialOffset(offset);


	_anim->playAnim(AnimatedSpriteComponent::None);

	_transform->setDefaultAnchor(0.1, 0.6); //Parametros para la pistola
}

void Arm::setTexture(Texture* texture)
{
	_anim->setTexture(texture);
}

void Arm::setAnimations(ArmAnimType type)
{
	switch (type)
	{
	case TurretArmType:
		_anim->addAnim(AnimatedSpriteComponent::None, 12, true);
		_anim->addAnim(AnimatedSpriteComponent::Shoot, 9, false);
		break;
	case BHCannonArmType:
		_anim->addAnim(AnimatedSpriteComponent::None, 2, true);
		_anim->addAnim(AnimatedSpriteComponent::Shoot, 6, false);
		_anim->addAnim(AnimatedSpriteComponent::NoAmmo, 2, false);
		break;
	case PlayerShotgunArmType:
		_anim->addAnim(AnimatedSpriteComponent::None, 1, false);
		_anim->addAnim(AnimatedSpriteComponent::Shoot, 2, false);
		_anim->addAnim(AnimatedSpriteComponent::NoAmmo, 2, false);
		_anim->addAnim(AnimatedSpriteComponent::Reload, 5, false);
		break;
	case PlayerPistolArmType:
		_anim->addAnim(AnimatedSpriteComponent::None, 1, false);
		_anim->addAnim(AnimatedSpriteComponent::Shoot, 2, false);
		_anim->addAnim(AnimatedSpriteComponent::NoAmmo, 2, false);
		_anim->addAnim(AnimatedSpriteComponent::Reload, 13, false);
		break;
	case PlayerRifleArmType:
		_anim->addAnim(AnimatedSpriteComponent::None, 1, false);
		_anim->addAnim(AnimatedSpriteComponent::Shoot, 2, false);
		_anim->addAnim(AnimatedSpriteComponent::NoAmmo, 2, false);
		_anim->addAnim(AnimatedSpriteComponent::Reload, 14, false);
		break;
	case DefaultArmType:
	default:
		_anim->addAnim(AnimatedSpriteComponent::None, 1, false);
		_anim->addAnim(AnimatedSpriteComponent::Shoot, 2, false);
		_anim->addAnim(AnimatedSpriteComponent::NoAmmo, 2, false);
		break;
	}
}

void Arm::lookAtTarget(const Vector2D& target) const
{
	Vector2D subVec = target - _transform->getPosition();
	subVec.normalize();

	double angle = atan2(subVec.getY(), subVec.getX()) * 180.0 / M_PI;

	_transform->setRotation(angle);
}

void Arm::hurt() const
{
	_anim->hurt();
}

void Arm::die() const
{
	_anim->die();
}