#include "ExampleObject.h"
#include "SpriteComponent.h"
#include "MovingComponent.h"
#include "PlayerControllerComponent.h"



ExampleObject::ExampleObject(Vector2D pos, Texture* texture) : GameComponent() 
{
	_transform = new TransformComponent(pos, Vector2D(5, 5), Vector2D(0.5, 0.5));
	addRenderComponent(new SpriteComponent(_transform, texture));

	MovingComponent* a = new MovingComponent(_transform, Vector2D(0, 0), 3);

	addPhysicsComponent(a);
	addInputComponent(new PlayerControllerComponent(a));
	
}

void ExampleObject::update() 
{
	GameComponent::update();

	//transform->setRotation(transform->getRotation() + 0.2);
}
