#include "Gun.h"
#include "AnimatedSpriteComponent.h"


Gun::Gun(GameComponent* shootingObj, int maxAmmo, int maxClip) : _shootingObj(shootingObj), _maxAmmo(maxAmmo), _maxClip(maxClip), _leftAmmo(maxAmmo), _leftClip(maxClip), GameComponent()
{
	//en principio su transform es el mismo que el del jugador;
	//_playerTransform = player->getComponent<TransformComponent>();

	auto transform = addComponent<TransformComponent>(); //new TransformComponent();
	addComponent<AnimatedSpriteComponent>();
	//addRenderComponent(new SpriteComponent(transform, texture));


}


Gun::~Gun()
{
	//_playerTransform = nullptr;
}

void Gun::update()
{
	//getComponent<TransformComponent>()->setPosition(_playerTransform->getPosition().getX(), _playerTransform->getPosition().getY());
}