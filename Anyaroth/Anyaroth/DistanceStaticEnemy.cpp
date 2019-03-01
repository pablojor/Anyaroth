#include "DistanceStaticEnemy.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"


DistanceStaticEnemy::DistanceStaticEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : Enemy(player, g, play, texture, posIni, tag)
{
	_vision = 500;
	_attackRange = 30; //No se puede poner mas peque�o que la velocidad
	_attackTime = 1300; //La animacion tarda unos 450
	_life = 50;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
}

void DistanceStaticEnemy::update()
{
	Enemy::update();

	BodyComponent* _playerBody = _player->getComponent<BodyComponent>();

	b2Vec2 enemyPos = _body->getBody()->GetPosition(), 
			playerPos = _playerBody->getBody()->GetPosition();

	double x = playerPos.x * 8 - enemyPos.x * 8,
			y = playerPos.y * 8 - enemyPos.y * 8;

	if (x < _vision && x > -_vision && y < _vision && y > -_vision) //Jugador en el rango
	{
		if (x > 0) //Derecha
			_anim->unFlip();
		else if (x < 0) //Izquierda
			_anim->flip();

		//---RAYCAST
		b2RayCastInput rayInput;

		rayInput.maxFraction = 1;
		rayInput.p1 = { (float32)(enemyPos.x),
						(float32)(enemyPos.y - _body->getH()) };
		rayInput.p2 = { (float32)(playerPos.x),
						(float32)(playerPos.y - _playerBody->getH()) };

		bool hit = false;
		b2RayCastOutput rayOutput;

		for (b2Body* b = getWorld()->GetBodyList(); b && !hit; b = b->GetNext())
			for (b2Fixture* f = b->GetFixtureList(); f && !hit; f = f->GetNext())
				if (b->GetType() == b2_staticBody && f->RayCast(&rayOutput, rayInput, 0))
					hit = true;
		//---------------

		if (!hit) //Si vemos al jugador
		{
			cout << "MORITE AJQUEROSO" << endl;
		}
	}
}