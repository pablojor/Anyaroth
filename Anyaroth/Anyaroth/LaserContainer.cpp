#include "LaserContainer.h"


LaserContainer::LaserContainer(Game* g, Vector2D pos, Texture* container, Texture* laser, Player* player) : GameObject(g)
{
	addComponent<Texture>(container);

	auto transform = addComponent<TransformComponent>();
	transform->setPosition(pos.getX(), pos.getY());

	addComponent<SpriteComponent>();

	_laser = new Laser(g, pos, laser, player, 5);

	addChild(_laser);
}
