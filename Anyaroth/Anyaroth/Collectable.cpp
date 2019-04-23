#include "Collectable.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "Game.h"

Collectable::Collectable(Game* game, Texture* texture, Vector2D pos, int value, string tag) : GameObject(game, tag), _value(value)
{
	addComponent<Texture>(texture);

	auto transform = addComponent<TransformComponent>();
	transform->setPosition(pos.getX(), pos.getY());

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_dynamicBody);
	_body->filterCollisions(OBJECTS, PLAYER | FLOOR | PLATFORMS);
	_body->getBody()->SetGravityScale(0.4);
}

void Collectable::collect()
{
	_body->filterCollisions(COLLECTED_OBJECTS, COLLECTED_OBJECTS);
	destroy();
}