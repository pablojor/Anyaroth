#include "ExampleObject.h"
#include "SpriteComponent.h"



ExampleObject::ExampleObject(TextureComponent* texture, unsigned int width, unsigned int height) : GameComponent() {
	transform = new TransformComponent();
	addRenderComponent(new SpriteComponent(transform, texture, width, height));
	transform->setScale(10, 10);
	transform->setPosition(0, 0);
}


ExampleObject::~ExampleObject()
{
}
