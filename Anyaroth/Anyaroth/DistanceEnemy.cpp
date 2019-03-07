#include "DistanceEnemy.h"
#include "Game.h"

DistanceEnemy::DistanceEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : Enemy(player, g, play, texture, posIni, tag)
{
	_arm = new EnemyArm(getGame()->getTexture("ArmPistol"), this, player, getGame(), _play, { 35,30 });
	addChild(_arm);

	ShooterInterface* sh = getGame()->gameGuns[BasicEnemyGun].shooter;
	GunType type = GunType(getGame()->gameGuns[BasicEnemyGun].type);

	int mA = getGame()->gameGuns[BasicEnemyGun].maxAmmo;
	int mC = getGame()->gameGuns[BasicEnemyGun].maxClip;

	// TEMPORAL
	PoolWrapper* bp = _play->getBulletPool(type);
	bp->changePoolTag("EnemyBullet");

	_arm->setGun(new Gun(_arm, sh, bp, type, mA, mC));
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