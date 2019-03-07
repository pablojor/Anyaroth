#include "Arm.h"
#include "PlayState.h"
#include "Gun.h"

Arm::Arm(Texture* texture, GameComponent* owner, Game* g, PlayState* play, Vector2D offset) : GameComponent(g)
{
	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();

	_anim = addComponent<AnimatedSpriteComponent>();

	if (owner != nullptr)
		setOwner(offset, owner);

	_cam = play->getMainCamera();

	_anim->addAnim(AnimatedSpriteComponent::None, 1, false);
	_anim->addAnim(AnimatedSpriteComponent::Shoot, 2, false);
	_anim->addAnim(AnimatedSpriteComponent::NoAmmo, 2, false);
	_anim->playAnim(AnimatedSpriteComponent::None);

	_transform->setDefaultAnchor(0.1, 0.6); //Parametros para la pistola
}

Arm::~Arm()
{
	delete _currentGun;
	_currentGun = nullptr;
}

void Arm::setArmSprite(Texture* armTex)
{
	_anim->setTexture(armTex);
}

void Arm::rotate(Vector2D target)
{
	Vector2D direction = _transform->getPosition() - target;

	direction.normalize();

	//Distancia del mouse al brazo
	double distance = target.distance(_transform->getPosition());

	//Actualizo angulo del brazo
	double rot = atan2(direction.getY(), direction.getX()) * 180.0 / PI;

	if (!_anim->isFlipped())
		rot -= 180;

	_transform->setRotation(rot);
}

void Arm::setOwner(Vector2D offset, GameComponent* owner)
{
	_owner = owner;
	_followC = addComponent<FollowingComponent>(_owner);
	_followC->setInitialOffset(offset);
}

//Dispara el arma
void Arm::shoot()
{
	if (_currentGun != nullptr)
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
	}
}

void Arm::setGun(Gun* gun)
{
	if (_currentGun != nullptr) //Si ya hay un arma, llama a su destructora
		delete _currentGun;

	_currentGun = gun;
}