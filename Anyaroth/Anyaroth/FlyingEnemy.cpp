#include "FlyingEnemy.h"
#include "Game.h"

FlyingEnemy::FlyingEnemy(Game* g, Player* player, Vector2D pos) : Enemy(g,  player, pos, g->getTexture("EnemyMelee"))
{
	_damage = 10;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	_body->filterCollisions(ENEMY_BULLETS, PLAYER);
	_body->getBody()->SetGravityScale(0);
	_body->getBody()->GetFixtureList()->SetSensor(true);

	_originalPos= Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	_previousPos = _originalPos;
}

void FlyingEnemy::sinusoidalMove(const double& deltaTime)
{
	//Onda Sinusoidal vertical 
	double prevX = _body->getBody()->GetPosition().x * M_TO_PIXEL + _velocity.getX() * _dir.getX();
	double prevY = _previousPos.getY() + _velocity.getY() * _dir.getY();

	_previousPos = Vector2D(prevX, prevY);

	double y = prevY + _amplitude * sin(_k * prevX - _angularFrequency * deltaTime / 1000);

	if (_originalPos.distance(_previousPos) < _maxDistance)
		_body->getBody()->SetTransform(b2Vec2(prevX / M_TO_PIXEL, y / M_TO_PIXEL), 0);
}

void FlyingEnemy::update(const double& deltaTime)
{
	Enemy::update(deltaTime);

	_dir = Vector2D((_playerDistance.getX() < 0) ? -1 : 1, (_playerDistance.getY() < 0) ? -1 : 1);

	if (_dir.getX() < 0)
		_anim->flip();
	else
		_anim->unFlip();

	sinusoidalMove(deltaTime);
}

void FlyingEnemy::beginCollision(GameObject * other, b2Contact * contact)
{
	if (other->getTag() == "Player")
	{
		_player->subLife(_damage);
		destroy();
	}
}