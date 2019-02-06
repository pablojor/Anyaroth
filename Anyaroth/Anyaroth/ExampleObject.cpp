#include "ExampleObject.h"
#include "SpriteRenderer.h"



ExampleObject::ExampleObject(Texture* texture, unsigned int width, unsigned int height) : GameComponent() {
	addRenderComponent(new SpriteRenderer(this, texture, width, height));
	getTransform()->setScale(10, 10);
	getTransform()->setPosition(500, 500);
}


ExampleObject::~ExampleObject()
{
}
