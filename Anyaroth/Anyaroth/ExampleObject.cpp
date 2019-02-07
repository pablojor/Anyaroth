#include "ExampleObject.h"
#include "SpriteComponent.h"
#include "MovingComponent.h"



ExampleObject::ExampleObject(Texture* texture) : GameComponent() {
	_transform = new TransformComponent(Vector2D(720 / 2, 480 / 2), Vector2D(32, 32), Vector2D(10, 10), Vector2D(0.5, 0.5));
	auto a = new SpriteComponent(_transform, texture);
	addRenderComponent(a);
	//addPhysicsComponent(new MovingComponent(transform, 1, 1));
	//transform->setRotation(45);
	a->flip();
	
}

ExampleObject::~ExampleObject() {
}

void ExampleObject::update() {
	GameComponent::update();

	//transform->setRotation(transform->getRotation() + 0.2);
}
