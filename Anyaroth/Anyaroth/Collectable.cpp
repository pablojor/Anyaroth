#include "Collectable.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "Game.h"

Collectable::Collectable(Game* game, Texture* texture, Vector2D pos, int value, string tag, string sound) : GameObject(game, tag), _value(value), _pickSound(sound)
{
	addComponent<Texture>(texture);

	auto transform = addComponent<TransformComponent>();
	transform->setPosition(pos.getX(), pos.getY());

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_dynamicBody);
	_body->filterCollisions(OBJECTS, PLAYER | FLOOR | PLATFORMS);
	_body->getBody()->SetGravityScale(1.5);
	_body->getBody()->GetFixtureList()->SetRestitution(1);
}

void Collectable::beginCollision(GameObject* other, b2Contact* contact)
{
	_body->getBody()->SetLinearVelocity(b2Vec2(0.0, 0.0));
	_body->getBody()->SetAngularVelocity(0);

	if(other->getTag() == "Player")
		collect();
}

void Collectable::collect()
{
	_body->filterCollisions(COLLECTED_OBJECTS, COLLECTED_OBJECTS);
	destroy();
	_game->getSoundManager()->playSFX(_pickSound);
}