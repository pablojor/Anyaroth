#include "DistanceStaticEnemy.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"


DistanceStaticEnemy::DistanceStaticEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : game(g), Enemy(player, g, play, texture, posIni, tag)
{
	_vision = 500;
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
		
		if (x > 0) //MIRAR BODIES
		{
			rayInput.p1 = { (float32)(_body->getBody()->GetPosition().x + 1.6),
							(float32)(_body->getBody()->GetPosition().y - 3) };

			rayInput.p2 = { (float32)(_playerBody->getBody()->GetPosition().x - 2),
							(float32)(_playerBody->getBody()->GetPosition().y - 2.5) };
		}
		else if (x < 0)
		{
			rayInput.p1 = { (float32)(_body->getBody()->GetPosition().x - 1.6),
							(float32)(_body->getBody()->GetPosition().y - 3) };

			rayInput.p2 = { (float32)(_playerBody->getBody()->GetPosition().x + 2),
							(float32)(_playerBody->getBody()->GetPosition().y - 2.5)};
		}

		bool hit = false;
		b2RayCastOutput rayOutput;
		for (b2Body* b = getWorld()->GetBodyList(); b && !hit; b = b->GetNext())
			for (b2Fixture* f = b->GetFixtureList(); f && !hit; f = f->GetNext())
			{
				if (f->RayCast(&rayOutput, rayInput, 0))
				{
					hit = true;
				}
			}
		if (!hit)
		{
			cout << "MORITE AJQUEROSO" << endl;
		}

		game->getTexture("Punto2")->render({ (int)rayInput.p1.x * 8, (int)rayInput.p1.y * 8, 5, 5 });
		game->getTexture("Punto2")->render({ (int)rayInput.p2.x * 8, (int)rayInput.p2.y * 8, 5, 5 });
		SDL_RenderPresent(game->renderer);
	}
}