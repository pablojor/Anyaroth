#include "GroundEnemy.h"

GroundEnemy::GroundEnemy(Game* g, Player* player, Vector2D pos, Texture* texture) : Enemy(g, player, pos, texture)
{
	_body->getBody()->SetGravityScale(3);
	_affectedByExternalForces = true;
}

void GroundEnemy::idle()
{
	if (!_stunned && !_attacking)
	{
		_body->getBody()->SetLinearVelocity({ 0, _body->getBody()->GetLinearVelocity().y });
		_anim->playAnim(AnimatedSpriteComponent::Idle);
	}
}

void GroundEnemy::moving(Vector2D& dir)
{
	if (!_stunned && !_attacking)
	{
		if (!(collidingL && dir.getX() < 0) && !(collidingR && dir.getX() > 0))
		{
			_body->getBody()->SetLinearVelocity({ _speed*(float32)dir.getX(), _body->getBody()->GetLinearVelocity().y });
			_anim->playAnim(AnimatedSpriteComponent::EnemyWalk);
		}
		else
			idle();
	}
}

void GroundEnemy::attack()
{
	if (!_stunned && !_attacking)
	{
		_body->getBody()->SetLinearVelocity({ 0, _body->getBody()->GetLinearVelocity().y });
		_anim->playAnim(AnimatedSpriteComponent::EnemyAttack); //Llamas a animacion de ataque
		_game->getSoundManager()->playSFX("meleeEnemyAttack");
		_time = 0;
		_attacking = true;
	}
}

void GroundEnemy::addSensors()
{
	b2PolygonShape shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 2 / M_TO_PIXEL, b2Vec2(-2, 2), 0);
	b2FixtureDef fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = ENEMIES;
	fDef.filter.maskBits = FLOOR | PLATFORMS;
	fDef.isSensor = true;
	fDef.friction = -26;
	_body->addFixture(&fDef, this);

	shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 2 / M_TO_PIXEL, b2Vec2(2, 2), 0);
	fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = ENEMIES;
	fDef.filter.maskBits = FLOOR | PLATFORMS;
	fDef.isSensor = true;
	fDef.friction = 26;
	_body->addFixture(&fDef, this);
}

void GroundEnemy::beginCollision(GameObject * other, b2Contact* contact)
{
	Enemy::beginCollision(other, contact);

	string otherTag = other->getTag();
	auto fA = contact->GetFixtureA();
	auto fB = contact->GetFixtureB();

	//Deteccion del suelo
	if ((fA->IsSensor() || fB->IsSensor()) && (other->getTag() == "Ground" || other->getTag() == "Platform"))
		if (fA->GetFriction() == 26 || fB->GetFriction() == 26)
		{
			collidingR = true;
		}
		else if (fA->GetFriction() == -26 || fB->GetFriction() == -26)
		{
			collidingL = true;
		}
}

void GroundEnemy::endCollision(GameObject * other, b2Contact* contact)
{
	string otherTag = other->getTag();
	auto fA = contact->GetFixtureA();
	auto fB = contact->GetFixtureB();

	//Deteccion del suelo
	if ((fA->IsSensor() || fB->IsSensor()) && (other->getTag() == "Ground" || other->getTag() == "Platform"))
		if (fA->GetFriction() == 26 || fB->GetFriction() == 26)
		{
			collidingR = false;
		}
		else if (fA->GetFriction() == -26 || fB->GetFriction() == -26)
		{
			collidingL = false;
		}
}