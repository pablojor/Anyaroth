#include "Collectable.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "PlayState.h"

Collectable::Collectable(PlayState* play, Game* g, Texture* texture, Vector2D iniPos, int value, string tag) : _play(play), _value(value), GameComponent(g, tag)
{
	addComponent<Texture>(texture);

	auto transform = addComponent<TransformComponent>();
	transform->setPosition(iniPos.getX(), iniPos.getY());

	auto body = addComponent<BodyComponent>();
	body->getBody()->SetType(b2_kinematicBody);
	body->filterCollisions(OBJECTS, PLAYER);

	setActive(true);
}

void Collectable::destroy() 
{ 
	setActive(false);
	_play->KillObjects(_itList);
}