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

	b2Vec2 enemyPos = _body->getBody()->GetPosition(), 
			playerPos = _playerBody->getBody()->GetPosition();

	double x = playerPos.x - enemyPos.x,
			y = playerPos.y - enemyPos.y;

	if ((x != 0 || y > 0) && //el jugador esta debajo
		(x < _vision && x > -_vision && y < _vision && y > -_vision)) //estas viendo al jugador
	{
		b2RayCastInput rayInput;
		rayInput.maxFraction = 1;
		
		//------------MIRAR BODIES PORQUE NO TIENE SENTIDO-----------//

		if (x > 0) //jugador a la derecha
		{
			rayInput.p1 = { (float32)(enemyPos.x + 1.6),
							(float32)(enemyPos.y - 3) };

			rayInput.p2 = { (float32)(playerPos.x - 2),
							(float32)(playerPos.y - 2.5) };
		}
		else if (x < 0) //jugador a la izquierda
		{
			rayInput.p1 = { (float32)(enemyPos.x - 1.6),
							(float32)(enemyPos.y - 3) };

			rayInput.p2 = { (float32)(playerPos.x + 2),
							(float32)(playerPos.y - 2.5)};
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

		//PROV 
		//RENDERIZADO DE PUNTOS
		game->getTexture("Punto2")->render({ (int)rayInput.p1.x * 8, (int)rayInput.p1.y * 8, 5, 5 });
		game->getTexture("Punto2")->render({ (int)rayInput.p2.x * 8, (int)rayInput.p2.y * 8, 5, 5 });
		SDL_RenderPresent(game->renderer);
	}
}