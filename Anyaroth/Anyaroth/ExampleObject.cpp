#include "ExampleObject.h"
#include "SpriteRenderer.h"



ExampleObject::ExampleObject(Texture* texture, unsigned int width, unsigned int height) : GameComponent() {
	transform = new Transform();
	addRenderComponent(new SpriteRenderer(transform, texture, width, height));
	transform->setScale(10, 10);
	transform->setPosition(0, 0);
}


ExampleObject::~ExampleObject()
{
}
