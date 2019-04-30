#include "Axe.h"
#include "Game.h"
#include <math.h>

Axe::Axe(Game * g, Vector2D offset, Uint16 collidesWith, double damage, double w, double h, double iniAngle) : Melee(g, offset, collidesWith, damage, w, h, Sword_Weapon), _angle(iniAngle), _iniAngle(iniAngle) {}

void Axe::meleeAttack(double x, double y, int dir)
{
	Melee::meleeAttack(x, y, dir);
	_angle = (_dir == 1) ? _iniAngle-40 :  _iniAngle+40;
}

void Axe::update(const double& deltaTime)
{
	if (isActive())
	{
		_angle += 4 * _dir;
		double x, y;
		x = _center.getX() + _r * cos(_angle *M_PI / 180);
		y = _center.getY() + _r * sin(_angle * M_PI / 180);
		_body->getBody()->SetTransform(b2Vec2(x / M_TO_PIXEL, y / M_TO_PIXEL), 0);
	}
}