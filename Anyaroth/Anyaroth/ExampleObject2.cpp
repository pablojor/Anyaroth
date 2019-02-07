#include "ExampleObject2.h"
#include "SpriteComponent.h"
#include "MovingComponent.h"
#include "PlayerControllerComponent.h"



ExampleObject2::ExampleObject2(Vector2D pos, Texture* texture) : GameComponent()
{
	_transform = new TransformComponent(pos, Vector2D(5, 5), Vector2D(0.5, 0.5));
	addRenderComponent(new SpriteComponent(_transform, texture));

	collider = new BoxCollider(_transform, texture);
	addPhysicsComponent(collider);
}

void ExampleObject2::update()
{
	GameComponent::update();

	//transform->setRotation(transform->getRotation() + 0.2);
}