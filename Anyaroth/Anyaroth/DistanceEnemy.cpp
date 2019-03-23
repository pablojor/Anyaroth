#include "DistanceEnemy.h"
#include "Game.h"
#include "BasicPistol.h"

DistanceEnemy::DistanceEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, BulletPool* pool) : Enemy(g, player, texture, posIni, tag)
{
	_arm = new EnemyArm(g, this, player, this, { 35, 30 });
	_arm->setTexture(g->getTexture("ArmPistol"));
	addChild(_arm);

	_myGun = new BasicPistol(g);

	_myBulletPool = pool;
}

void DistanceEnemy::RayCast()
{
	BodyComponent* target = _player->getComponent<BodyComponent>();

	b2Vec2 enemyPos = _body->getBody()->GetPosition();
	b2Vec2 targetPos = target->getBody()->GetPosition();

	b2RayCastInput rayInput;

	rayInput.maxFraction = 1;
	rayInput.p1 = { (float32)(enemyPos.x), (float32)(enemyPos.y - _body->getH()) };
	rayInput.p2 = { (float32)(targetPos.x), (float32)(targetPos.y) };

	b2RayCastOutput rayOutput;

	_armVision = true;

	for (b2Body* b = getWorld()->GetBodyList(); b && _armVision; b = b->GetNext())
		for (b2Fixture* f = b->GetFixtureList(); f && _armVision; f = f->GetNext())
			if (b->GetType() == b2_staticBody && f->RayCast(&rayOutput, rayInput, 0))
				_armVision = false;
}

void DistanceEnemy::update(const double& deltaTime)
{
	Enemy::update(deltaTime);

	_myGun->refreshGunCadence(deltaTime);
}