#include "DistanceStaticEnemy.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"


DistanceStaticEnemy::DistanceStaticEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : Enemy(player, g, play, texture, posIni, tag)
{
	_vision = 300;
	_attackRange = _vision; //No se puede poner mas peque�o que la velocidad
	_attackTime = 1300; //La animacion tarda unos 450
	_life = 50;


	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
}

void DistanceStaticEnemy::update()
{
	Enemy::update();

	BodyComponent* _playerBody = _player->getComponent<BodyComponent>();
	TransformComponent* _playerTransform = _player->getComponent<TransformComponent>();

	Vector2D enemy, player;

	enemy = _transform->getPosition();
	player = _playerTransform->getPosition();

	double x, y;

	x = player.getX() - enemy.getX();
	y = player.getY() - enemy.getY();

	if ((x != 0 || y > 0) &&
		(x < _vision && x > -_vision && y < _vision && y > -_vision)) //estas viendo al jugador
	{
		b2RayCastInput rayInput;
		rayInput.maxFraction = 1;

		if (x > 0)
		{
			rayInput.p1 = { (float32)(enemy.getX() + _body->getW()) / 8, (float32)enemy.getY() / 8 };
			rayInput.p2 = { (float32)player.getX() / 8, (float32)player.getY() / 8 };
		}
		else if (x < 0)
		{
			rayInput.p1 = { (float32)enemy.getX() / 8, (float32)enemy.getY() / 8 };
			rayInput.p2 = { (float32)(player.getX() + _playerBody->getW()) / 8, (float32)player.getY() / 8 };
		}

		b2RayCastOutput rayOutput;
		if (!_body->getBody()->GetFixtureList()->RayCast(&rayOutput, rayInput, 0))
			cout << "MORITE AJQUEROSO" << endl;
	}
}