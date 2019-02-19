#include "Collectable.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"

Collectable::Collectable(Game* g, Texture* texture, Vector2D iniPos, int value) : _value(value), GameComponent(g)
{
	addComponent<Texture>(texture);

	auto transform = addComponent<TransformComponent>();
	transform->setPosition(iniPos.getX(), iniPos.getY());

	auto body = addComponent<BodyComponent>();

	addComponent<SpriteComponent>();
}