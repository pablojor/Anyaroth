#include "DistanceStaticEnemy.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"

DistanceStaticEnemy::DistanceStaticEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : DistanceEnemy(player, g, play, texture, posIni, tag)
{
	_vision = 700;
	_attackRange = _vision; //No se puede poner mas pequeño que la velocidad
	_attackTime = 1300; //La animacion tarda unos 450
	_life = 50;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
}

void DistanceStaticEnemy::update(double time)
{
	Enemy::update(time);

	BodyComponent* _playerBody = _player->getComponent<BodyComponent>();

	b2Vec2 enemyPos = _body->getBody()->GetPosition(), playerPos = _playerBody->getBody()->GetPosition();

	double x = playerPos.x * 8 - enemyPos.x * 8, y = playerPos.y * 8 - enemyPos.y * 8;

	if (x < _vision && x > -_vision && y < _vision && y > -_vision) //Jugador en el rango
	{
		RayCast();

		if (_armVision) //Si vemos al jugador
		{
			if (x > 0) //Derecha
				_anim->unFlip();
			else if (x < 0) //Izquierda
				_anim->flip();

			//_arm->shoot();
		}
	}
}