#include "StaticSpawnerEnemy.h"
#include "FlyingEnemy.h"

StaticSpawnerEnemy::StaticSpawnerEnemy(Game * g, Player * player, Vector2D pos) : Enemy(g, player, pos, g->getTexture("EnemyMartyr"))
{
	_life = 300;
	_time = 0;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
}

void StaticSpawnerEnemy::update(const double& deltaTime)
{
	Enemy::update(deltaTime);

	bool inVision = _playerDistance.getX() < _vision && _playerDistance.getX() > -_vision && _playerDistance.getY() < _vision && _playerDistance.getY() > -_vision;

	if (!isDead() && inCamera() && inVision)
	{
		_currentEnemies = activeEnemies();

		if (_time >= _spawnTime && _currentEnemies < _maxEnemies)
		{
			addChild(new FlyingEnemy(_game, _player, Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL - TILES_SIZE * 2, _body->getBody()->GetPosition().y * M_TO_PIXEL - TILES_SIZE * 2)));
			_time = 0;
		}
		else
			_time += deltaTime;
	}
	else if (isDead())
		destroyAllChildren();
}

int StaticSpawnerEnemy::activeEnemies()
{
	return getChildren().size();
}