#include "Boss2.h"



Boss2::Boss2(Game* g, Player* player, Vector2D pos, BulletPool* pool) : Boss(g, player, pos, pool), Enemy(g, player, pos, g->getTexture("EnemyMelee"))
{

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);
	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
	_body->addCricleShape(b2Vec2(0, 1.1), 0.7, PLAYER, FLOOR | PLATFORMS);
	

	_body->filterCollisions(ENEMIES, FLOOR | PLAYER_BULLETS | MELEE);
	_body->getBody()->SetFixedRotation(true);
	_body->getBody()->SetGravityScale(3.5);
	
	_originalPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	
	b2PolygonShape shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 3 / M_TO_PIXEL, b2Vec2(0, 3), 0);
	b2FixtureDef fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = ENEMIES;
	fDef.filter.maskBits = FLOOR | PLATFORMS;
	fDef.isSensor = true;
	_body->addFixture(&fDef, this);

	_armVision = true;

	_playerBody = _player->getComponent<BodyComponent>();
}


Boss2::~Boss2()
{
}

void Boss2::Jump()
{
	_playerPos = Vector2D(_playerBody->getBody()->GetPosition().x * M_TO_PIXEL, _playerBody->getBody()->GetPosition().y * M_TO_PIXEL);
	_jump = true;
	int dir = (_body->getBody()->GetPosition().x* M_TO_PIXEL >= _playerPos.getX()) ? -1 : 1;
	
	_body->getBody()->ApplyLinearImpulseToCenter(b2Vec2(dir * 300, -300), true);
	
	_doSomething = random(2000, 3000);
}


void Boss2::beginCollision(GameObject * other, b2Contact* contact)
{
	auto fA = contact->GetFixtureA();
	auto fB = contact->GetFixtureB();

	Boss::beginCollision(other, contact);
	//Deteccion del suelo
	if ((fA->IsSensor() || fB->IsSensor()) && (other->getTag() == "Ground" || other->getTag() == "Platform"))
	{
		_jump = false;
	}
	
	
}


void Boss2::fase1(const double& deltaTime)
{
	//_body->getBody()->SetLinearVelocity(b2Vec2(15, 0));
			if (_noAction > _doSomething)
			{
				//if (!_jump)
				
					Jump();
					_noAction = 0;
				/*int ra = random(0, 100);

				if (ra >= 65)
				{
					_actualState = Moving;
					
					
				}

				else
				{
					//armShoot(deltaTime);
					_actualState = Moving;
					_doSomething = random(400, 800);
					_noAction = 0;
				}*/
			}
			else
				_noAction += deltaTime;
	
}


void Boss2::beetwenFases(const double& deltaTime)
{
	if (_lastFase == Fase1)
		changeFase(Fase2);
	else if (_lastFase == Fase2)
		changeFase(Fase3);
	else
	{
		die();
	}
}
