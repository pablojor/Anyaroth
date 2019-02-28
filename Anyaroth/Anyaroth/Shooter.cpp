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



void Shooter::shoot(Vector2D bulletPosition, Vector2D bulletDir, double angle)
{
	_bPool->addBullet(bulletPosition, bulletDir, angle);
}