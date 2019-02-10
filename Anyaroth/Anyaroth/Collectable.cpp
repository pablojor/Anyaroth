#include "Collectable.h"
#include "SpriteComponent.h"


Collectable::Collectable(Texture* texture, Vector2D iniPos) : GameComponent()
{
	auto transform = addComponent<TransformComponent>();
	addComponent<SpriteComponent>();

	transform->setPosition(iniPos.getX(), iniPos.getY());
}
