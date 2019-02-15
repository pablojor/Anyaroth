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
	auto body = addComponent<BodyComponent>();
	auto anim = addComponent<AnimatedSpriteComponent>();		//Como depende de Transform, en su constructura crea una si no ha encontrado Transform en el objeto.
	addComponent<MovingComponent>();
	addComponent<PlayerControllerComponent>();
	body->getBody()->SetType(b2_dynamicBody);
	anim->addAnim("Idle", 16);
	anim->addAnim("Walk", 10);

	transform->setScale(RESOLUTION); //el 3 sería el factor de resolución!!
	//transform->setRotation(45);
}

Player::~Player() {
}

void Player::beginCollision(GameComponent * other)
{
	cout << "colision";
}

void Player::update() {
	GameComponent::update();

	//transform->setRotation(transform->getRotation() + 0.2);
}