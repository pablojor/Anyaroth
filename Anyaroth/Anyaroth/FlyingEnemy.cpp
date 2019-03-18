#include "FlyingEnemy.h"
#include "BodyComponent.h"
#include "Game.h"

FlyingEnemy::FlyingEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : Enemy( player,  g,  play,  texture, posIni, tag)
{
	_body->filterCollisions(ENEMIES, FLOOR);
	_body->getBody()->SetGravityScale(0);

	oY= _body->getBody()->GetTransform().p.y ;
}


FlyingEnemy::~FlyingEnemy()
{
}

void FlyingEnemy::update(double time)
{
	double x = _body->getBody()->GetPosition().x +0.05;
	double y = 5 * sin(1 * x - 0.05 * time)+ oY;
	_body->getBody()->SetTransform(b2Vec2(x, y),0);

	cout << x << " " << y<<endl;
}
