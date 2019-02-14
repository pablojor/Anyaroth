#include "HUD.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"

HUD::HUD(Texture* texture, b2Vec2 iniPos) : GameComponent()
{
	auto body = addComponent<BodyComponent>();
	addComponent<SpriteComponent>();

	body->getBody()->SetTransform(b2Vec2(iniPos.x, iniPos.y), body->getBodyDef().angle);
}

HUD::~HUD()
{
}