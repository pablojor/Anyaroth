#include "DistanceDynamicEnemy.h"
#include "GameObject.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"

DistanceDynamicEnemy::DistanceDynamicEnemy(Game* g, Player* player, Vector2D pos, BulletPool* pool) : DistanceEnemy(g, player, pos, g->getTexture("EnemyMelee"), pool)
{
	_vision = 300;
	_life = 50;
	_speed = 8;
	_attackRangeX = _attackRangeY = _vision / 2; //No se puede poner mas pequeño que la velocidad
	_attackTime = 1300; //La animacion tarda unos 450

	if (_attackRangeX < _speed)
		_attackRangeX += _speed;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	_body->addCricleShape(b2Vec2(0, _body->getH() + _body->getH() / 20), _body->getW() - _body->getW() / 20, ENEMIES, FLOOR);
}

void DistanceDynamicEnemy::update(const double& deltaTime)
{
	DistanceEnemy::update(deltaTime);

	if (!_dead && inCamera())
	{
		bool inVision = _playerDistance.getX() < _vision && _playerDistance.getX() > -_vision && _playerDistance.getY() < _vision && _playerDistance.getY() > -_vision;

		if (!_attacking && inVision) //Me acerco al jugador
		{
			if (_playerDistance.getX() > 0)//Derecha
			{
				_anim->unFlip();
				_dir = Vector2D(1, 0);

				if (_playerDistance.getX() > _attackRangeX)
					moving(_dir);
				else
					attack();
			}
			else if (_playerDistance.getX() < 0)//Izquierda
			{
				_anim->flip();
				_dir = Vector2D(-1, 0);

				if (_playerDistance.getX() < -_attackRangeX)
					moving(_dir);
				else
					attack();
			}
		}
		else if (_attacking) //Ya estoy a una distancia optima, ataco al jugador
			attacking(deltaTime);
		else
			idle();
	}
}

void DistanceDynamicEnemy::idle()
{
	if (_attacking == false)
	{
		_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
		_anim->playAnim(AnimatedSpriteComponent::Idle);
	}
}

void DistanceDynamicEnemy::moving(Vector2D& dir)
{
	if (_attacking == false)
	{
		_body->getBody()->SetLinearVelocity({ _speed*(float32)dir.getX(), _body->getBody()->GetLinearVelocity().y });
		_anim->playAnim(AnimatedSpriteComponent::EnemyWalk);
	}
}

void DistanceDynamicEnemy::attack()
{
	if (_attacking == false)
	{
		_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
		_anim->playAnim(AnimatedSpriteComponent::EnemyAttack); //Llamas a animacion de ataque
		_time = 0;
		_attacking = true;
	}
}

void DistanceDynamicEnemy::attacking(const double& deltaTime)
{
	bool outRange = _playerDistance.getX() < -_attackRangeX || _playerDistance.getX() > _attackRangeX || _playerDistance.getY() < -_attackRangeY || _playerDistance.getY() > _attackRangeY;

	if (outRange) //Si has perdido de vista al jugador dejas de atacar
		_attacking = false;
	else
	{
		raycast();
		shoot();

		if(!_armVision)
			_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
	}
}