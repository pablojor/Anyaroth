#include "Player.h"
#include "SpriteComponent.h"
#include "MovingComponent.h"
#include "PlayerControllerComponent.h"



Player::Player(Texture* texture) : GameComponent() {

	transform = new TransformComponent();
	addRenderComponent(new SpriteComponent(transform, texture));
	/*
	
	MovingComponent* a = new MovingComponent(transform, 0, 0);

	addPhysicsComponent(a);
	addInputComponent(new PlayerControllerComponent(a));




	transform->setScale(10);
	transform->setPosition(720 / 2, 480 / 2);
	transform->setAnchor(0.5, 0.5);
	//transform->setRotation(45);
	
	*/
	
}

Player::~Player() {
}

void Player::update() {
	GameComponent::update();

	//transform->setRotation(transform->getRotation() + 0.2);
}