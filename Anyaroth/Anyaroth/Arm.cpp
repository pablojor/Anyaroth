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

	_anim->addAnim(AnimatedSpriteComponent::None, 1, false);
	_anim->addAnim(AnimatedSpriteComponent::Shoot, 2, false);
	_anim->addAnim(AnimatedSpriteComponent::NoAmmo, 2, false);
	_anim->playAnim(AnimatedSpriteComponent::None);

	_transform->setDefaultAnchor(0.1, 0.6); //Parametros para la pistola
}

void Arm::setTexture(Texture* texture)
{
	_anim->setTexture(texture);
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