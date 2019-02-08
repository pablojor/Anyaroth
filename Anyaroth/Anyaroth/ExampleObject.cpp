#include "ExampleObject.h"
#include "SpriteComponent.h"
#include "MovingComponent.h"
#include "PlayerControllerComponent.h"



ExampleObject::ExampleObject(Texture* texture) : GameComponent() {

	addComponent<TransformComponent>();
	addComponent<TransformComponent>();

	auto a = getComponent<TransformComponent>();

	//addRenderComponent(new SpriteComponent(transform, texture));

	//MovingComponent* a = new MovingComponent(transform, 0, 0);

	//addPhysicsComponent(a);
	//addInputComponent(new PlayerControllerComponent(a));




	//transform->setScale(10);
	//transform->setPosition(720 / 2, 480 / 2);
	//transform->setAnchor(0.5, 0.5);
	//transform->setRotation(45);
	
}

ExampleObject::~ExampleObject() {
}

void ExampleObject::update() {
	GameComponent::update();

	//transform->setRotation(transform->getRotation() + 0.2);
}
