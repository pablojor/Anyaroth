#include "Bullet.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "MovingComponent.h"

Bullet::Bullet() : GameComponent() 
{
	/*
	addComponent<Texture>(texture);

	auto transform = addComponent<TransformComponent>();
	transform->setPosition(iniPos.getX(), iniPos.getY());

	auto body = addComponent<BodyComponent>();

	addComponent<SpriteComponent>();
	addComponent<MovingComponent>();*/
}

Bullet::~Bullet() 
{
}