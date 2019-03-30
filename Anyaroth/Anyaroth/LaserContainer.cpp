#include "LaserContainer.h"


LaserContainer::LaserContainer(Game * g, Vector2D pos, Texture* texture) : GameObject(g)
{
	addComponent<Texture>(texture);

	auto transform = addComponent<TransformComponent>();
	transform->setPosition(pos.getX(), pos.getY());

	addComponent<SpriteComponent>();
}
