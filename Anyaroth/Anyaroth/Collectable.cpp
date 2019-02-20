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

	addComponent<SpriteComponent>();
}

void Collectable::destroy() 
{ 
	_play->KillObject(_itList); 
}