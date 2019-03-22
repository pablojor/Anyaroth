#include "Axe.h"
#include "Game.h"
#include <math.h>

Axe::Axe(Game* g) : Melee(g)
{
	_offset = Vector2D(15, -20);
}

void Axe::update(const double& deltaTime)
{
	if (isActive())
	{
		_angle += 10 * _dir;
		double x, y;
		x = _center.getX() + _r * cos(_angle *M_PI / 180);
		y = _center.getY() + _r * sin(_angle * M_PI / 180);
		_body->getBody()->SetTransform(b2Vec2(x / M_TO_PIXEL, y / M_TO_PIXEL), 0);
	}
	else
		_angle = 90;
}