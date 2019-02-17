#include "Player.h"
#include "PlayerControllerComponent.h"
#include "TransformComponent.h"
#include "MovingComponent.h"
#include "BoxCollider.h"
#include "Game.h"

Player::Player(Texture* texture, Game* g) : GameComponent(g)
{
	//Siempre primero los componentes que tienen que estar SI o SI.
	addComponent<Texture>(texture);

	//Resto de componentes
	auto transform = addComponent<TransformComponent>();		//Como en el metodo anterior se ha creado este componente, imprime por pantalla que ya existe uno.
	transform->setPosition(0, 50);
	transform->setScale(RESOLUTION);

	auto anim = addComponent<AnimatedSpriteComponent>();		//Como depende de Transform, en su constructura crea una si no ha encontrado Transform en el objeto.
	anim->addAnim("Idle", 16);
	anim->addAnim("Walk", 10);

	auto body = addComponent<BodyComponent>();
	body->getBody()->SetType(b2_dynamicBody);
	body->getBody()->SetBullet(true);
	body->getBody()->SetFixedRotation(true);

	addComponent<MovingComponent>();
	addComponent<PlayerControllerComponent>();
}

Player::~Player()
{
}

void Player::beginCollision(GameComponent * other)
{
	auto myTransform = this->getComponent<TransformComponent>();
	auto myControler = this->getComponent<PlayerControllerComponent>();

	auto otherTransform = other->getComponent<TransformComponent>();

	if (myTransform->getPosition().getY() < otherTransform->getPosition().getY())
		myControler->changeJump();
}

void Player::update() 
{
	GameComponent::update();
}