#include "ExampleObject.h"
#include "SpriteComponent.h"
#include "MovingComponent.h"



ExampleObject::ExampleObject(TextureComponent* texture) : GameComponent() {
	transform = new TransformComponent();
	auto a = new SpriteComponent(transform, texture);
	addRenderComponent(a);
	//addPhysicsComponent(new MovingComponent(transform, 1, 1));
	transform->setScale(10);
	transform->setPosition(1820 / 2, 980 / 2);
	transform->setAnchor(0.2, 0.7);
	//transform->setRotation(45);
	a->flip();
	
}

ExampleObject::~ExampleObject() {
}

void ExampleObject::update() {
	GameComponent::update();

	//transform->setRotation(transform->getRotation() + 0.2);
}
