#include "HUD.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"

HUD::HUD(Texture* texture, b2Vec2 iniPos, Game* g) : GameComponent(g)
{
	auto body = addComponent<BodyComponent>();
	addComponent<SpriteComponent>();

	body->getBody()->SetTransform(b2Vec2(iniPos.x, iniPos.y), body->getBody()->GetAngle());
}

HUD::~HUD()
{
}