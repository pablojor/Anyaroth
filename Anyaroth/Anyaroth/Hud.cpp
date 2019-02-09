#include "Hud.h"
#include "SpriteComponent.h"


Hud::Hud(Texture* texture, Vector2D iniPos) : GameComponent()
{
	transform = new TransformComponent();
	addRenderComponent(new SpriteComponent(transform, texture));

	transform->setPosition(iniPos.getX(), iniPos.getY());
}


Hud::~Hud()
{
}

