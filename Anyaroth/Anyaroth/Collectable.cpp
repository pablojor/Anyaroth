#include "Collectable.h"
#include "SpriteComponent.h"
#include "BodyComponent.h"

Collectable::Collectable(Texture* texture, b2Vec2 iniPos) : GameComponent()
{
	auto body = addComponent<BodyComponent>();
	addComponent<SpriteComponent>();

	body->getBody()->SetTransform(b2Vec2(iniPos.x, iniPos.y), body->getBodyDef().angle);
}