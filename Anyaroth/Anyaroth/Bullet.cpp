#include "Bullet.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "TransformComponent.h"
#include "MovingComponent.h"

Bullet::Bullet() : GameComponent() 
{
	addComponent<TransformComponent>();
	
}

Bullet::~Bullet() 
{
}


void Bullet::setTexture(Texture* texture)
{
	addComponent<Texture>(texture);

	auto anim = addComponent<AnimatedSpriteComponent>();
	anim->addAnim(AnimatedSpriteComponent::Default, 1, false);
	anim->playAnim(AnimatedSpriteComponent::Default);

	/*
	auto body = addComponent<BodyComponent>();
	body->getBody()->SetType(b2_dynamicBody);
	body->getBody()->SetBullet(true);
	body->getBody()->SetFixedRotation(true);
	//addComponent<BodyComponent>(); 
	addComponent<MovingComponent>();//Tiene que ir aquí porque necesita la textura
	*/
}