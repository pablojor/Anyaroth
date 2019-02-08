#include "ExampleObject.h"
#include "SpriteComponent.h"
#include "AnimatedSpriteComponent.h"
#include "AnimatedMovingComponent.h"
#include "PlayerControllerComponent.h"



ExampleObject::ExampleObject(Texture* texture) : GameComponent() {

	transform = new TransformComponent();
	//addRenderComponent(new SpriteComponent(transform, texture));
	AnimatedSpriteComponent* b = new AnimatedSpriteComponent(transform, texture);
	b->addAnim("Idle", 16);
	b->addAnim("Walk", 10);
	addRenderComponent(b);

	AnimatedMovingComponent* a = new AnimatedMovingComponent(transform, 0, 0, b);

	addPhysicsComponent(a);
	addInputComponent(new PlayerControllerComponent(a, b));




	transform->setScale(6,6);
	transform->setPosition(720 / 2, 480 / 2);
	transform->setAnchor(0.5, 0.5);
	//transform->setRotation(45);

}

ExampleObject::~ExampleObject() {
}

void ExampleObject::update() {
	GameComponent::update();

	//transform->setRotation(transform->getRotation() + 0.2);
}
