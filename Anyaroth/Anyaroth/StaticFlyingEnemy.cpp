#include "StaticFlyingEnemy.h"
#include "AnimatedSpriteComponent.h"
#include "BodyComponent.h"

StaticFlyingEnemy::StaticFlyingEnemy(Game* g, Player* player, Vector2D pos, BulletPool* pool) : DistanceStaticEnemy( g,  player,  pos,  pool), Enemy(g, player, pos, g->getTexture("AirTurret"))
{
	getComponent<BodyComponent>()->getBody()->SetGravityScale(0);
}


StaticFlyingEnemy::~StaticFlyingEnemy()
{
}
