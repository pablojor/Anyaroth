#include "Collectable.h"
#include "SpriteComponent.h"


Collectable::Collectable(Texture* texture, Vector2D iniPos) : GameComponent()
{
	transform = new TransformComponent();
	addRenderComponent(new SpriteComponent(transform, texture));

	transform->setPosition(iniPos.getX(), iniPos.getY());
}


Collectable::~Collectable()
{
}
