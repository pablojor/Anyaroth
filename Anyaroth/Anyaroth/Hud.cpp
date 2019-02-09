#include "Hud.h"
#include "SpriteComponent.h"


Hud::Hud(Texture* texture, Vector2D iniPos) : GameComponent()
{
	auto transform = addComponent<TransformComponent>();
	addComponent<SpriteComponent>();

	transform->setPosition(iniPos.getX(), iniPos.getY());
}


Hud::~Hud()
{
}

