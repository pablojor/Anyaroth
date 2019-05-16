#include "StaticSpawnerEnemy.h"
#include "FlyingEnemy.h"

StaticSpawnerEnemy::StaticSpawnerEnemy(Game * g, Player * player, Vector2D pos) : Enemy(g, player, pos, g->getTexture("Hive"),"staticSpawnerDeath", "martyrHit", "martyrMeleeHit")
{
	_vision = 500;
	_life = 40;
	_time = 0;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 9, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 1, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 8, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 10, false);

	_body->setW(30);
	_body->setH(20);

	_body->moveShape(b2Vec2(0, 0.6));
	_body->filterCollisions(ENEMIES, FLOOR | PLATFORMS | PLAYER_BULLETS | MELEE);
	_body->getBody()->SetFixedRotation(true);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
}

void StaticSpawnerEnemy::update(double deltaTime)
{
	Enemy::update(deltaTime);

	bool inVision = _playerDistance.getX() < _vision && _playerDistance.getX() > -_vision && _playerDistance.getY() < _vision && _playerDistance.getY() > -_vision;

	if (!isDead() && inCamera() && inVision)
	{
		_currentEnemies = activeEnemies();

		if (_time >= _spawnTime && _currentEnemies < _maxEnemies)
		{
			_anim->playAnim(AnimatedSpriteComponent::EnemyAttack);
			_time = 0;
		}
		else
			_time += deltaTime;

		if (_anim->getCurrentAnim() == AnimatedSpriteComponent::EnemyAttack && _anim->animationFinished())
		{
			addChild(new FlyingEnemy(_game, _player, Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL - TILES_SIZE * 2, _body->getBody()->GetPosition().y * M_TO_PIXEL - TILES_SIZE * 2)));
			_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
			_game->getSoundManager()->playSFX("staticSpawnerSpawn");
		}
	}
	else if (isDead())
	{
		destroyAllChildren();
	}
}

int StaticSpawnerEnemy::activeEnemies()
{
	return getChildren().size();
}