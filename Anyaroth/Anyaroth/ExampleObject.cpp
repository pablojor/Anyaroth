#include "ExampleObject.h"
#include "SpriteComponent.h"
#include "MovingComponent.h"
#include "PlayerControllerComponent.h"



ExampleObject::ExampleObject(Texture* texture) : GameComponent() 
{
	_transform = new TransformComponent(Vector2D(720 / 2, 480 / 2), Vector2D(32, 32), Vector2D(10, 10), Vector2D(0.5, 0.5));
	addRenderComponent(new SpriteComponent(_transform, texture));

	MovingComponent* a = new MovingComponent(_transform, 0, 0);

	addPhysicsComponent(a);
	addInputComponent(new PlayerControllerComponent(a));
	
}

ExampleObject::~ExampleObject() 
{
}

void ExampleObject::update() 
{
	GameComponent::update();

	//transform->setRotation(transform->getRotation() + 0.2);
}
