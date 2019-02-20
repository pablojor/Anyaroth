#include "Shooter.h"
#include "TransformComponent.h"
#include "MovingComponent.h"
#include "AnimatedSpriteComponent.h"


Shooter::Shooter()
{
}


Shooter::~Shooter()
{
}

void Shooter::init(GameComponent* shootingObject, PoolWrapper* bPool) 
{
	_shootingObject = shootingObject;
	_bPool = bPool;
}


void Shooter::shoot() 
{
	//Posición inicial de la bala
	Vector2D bulletPosition = _shootingObject->getComponent<TransformComponent>()->getPosition()
		+ Vector2D(_shootingObject->getComponent<AnimatedSpriteComponent>()->getTexture()->getW() / 2, _shootingObject->getComponent<AnimatedSpriteComponent>()->getTexture()->getH() / 2)
		+ (Vector2D(0, -1).rotate(_shootingObject->getComponent<TransformComponent>()->getRotation()))*(_shootingObject->getComponent<AnimatedSpriteComponent>()->getTexture()->getH() / 2 + 10);

	//Dirección de la bala
	Vector2D bulletDir = /*velocity_
						 + */(Vector2D(0, -1).rotate(_shootingObject->getComponent<TransformComponent>()->getRotation()));
	bulletDir.normalize();
	bulletDir = bulletDir * 3;


	_bPool->addBullet(bulletPosition, bulletDir);
}