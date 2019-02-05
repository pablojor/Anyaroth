#include "ExampleObject.h"
#include "SpriteRenderer.h"



ExampleObject::ExampleObject(Texture* texture, unsigned int width, unsigned int height) : GameComponent() {
	addRenderComponent(new SpriteRenderer(this, texture, width, height));
}


ExampleObject::~ExampleObject()
{
}
