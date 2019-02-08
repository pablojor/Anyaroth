#include "Gun.h"
#include "SpriteComponent.h"


Gun::Gun(Texture* texture, TransformComponent* player,int maxAmmunition,int magazine) : GameComponent()
{
	//en principio su transform es el mismo que el del jugador;
	playerTransform = player;
	transform = new TransformComponent();
	addRenderComponent(new SpriteComponent(transform, texture));

	maxAmmo = maxAmmunition;
	clip = magazine;
	ammoOnClip = magazine;
	if (maxAmmunition > magazine * 3)
	{
		leftAmmo = magazine * 2;
	}

}


Gun::~Gun()
{
	playerTransform = nullptr;
}

void Gun::update()
{
	transform->setPosition(playerTransform->getPosition().getX(), playerTransform->getPosition().getY());
}