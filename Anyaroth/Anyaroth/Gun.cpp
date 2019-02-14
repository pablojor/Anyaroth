#include "Gun.h"
#include "AnimatedSpriteComponent.h"

Gun::Gun(Texture* texture, GameComponent* player, int maxAmmunition, int magazine) : GameComponent()
{
	//en principio su transform es el mismo que el del jugador;
	_playerTransform = player->getComponent<BodyComponent>();

	auto transform = addComponent<TransformComponent>(); //new TransformComponent();
	addComponent<AnimatedSpriteComponent>();
	//addRenderComponent(new SpriteComponent(transform, texture));

	_maxAmmo = maxAmmunition;
	_clip = magazine;
	_ammoOnClip = magazine;
	if (maxAmmunition > magazine * 3)
	{
		_leftAmmo = magazine * 2;
	}
}


Gun::~Gun()
{
	_playerTransform = nullptr;
}

void Gun::update()
{
	getComponent<BodyComponent>()->getBody()->SetTransform(b2Vec2(_playerTransform->getBody()->GetPosition().x, _playerTransform->getBody()->GetPosition().y), _playerTransform->getBodyDef().angle);
}