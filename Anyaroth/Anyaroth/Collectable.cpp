#include "Collectable.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"

Collectable::Collectable(Game* g, Texture* texture, Vector2D iniPos, int value, string tag) : GameComponent(g, tag), _value(value)
{
	addComponent<Texture>(texture);

	auto transform = addComponent<TransformComponent>();
	transform->setPosition(iniPos.getX(), iniPos.getY());

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_kinematicBody);
	_body->filterCollisions(OBJECTS, PLAYER);

	setActive(true);
}

void Collectable::collect()
{
	_body->filterCollisions(COLLECTED_OBJECTS, COLLECTED_OBJECTS);
	setActive(false);
}