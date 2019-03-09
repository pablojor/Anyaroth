#include "Arm.h"
#include "Game.h"
#include <math.h>

Arm::Arm(Game* g, GameComponent* owner, Vector2D offset) : GameComponent(g), _owner(owner)
{
	addComponent<Texture>(g->getTexture("Arm"));
	_transform = addComponent<TransformComponent>();
	_anim = addComponent<AnimatedSpriteComponent>();

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

//Esta se va a pasar al los diferentes owners
void Arm::shoot()
{
	/*if (_currentGun != nullptr)
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

		_currentGun->shoot(bulletPosition, bulletDir, _anim->isFlipped());
	}*/
}