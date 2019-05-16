#include "Sword.h"
#include "Game.h"
#include <math.h>

//Valores del Sword en la constructora de Melee son los del Jugador(por defecto)
Sword::Sword(Game* game) : Melee(game, { 20, 0 }, ENEMIES, 10, 30, 20, Sword_Weapon) { _iniAngle = 90; }

void Sword::meleeAttack(double x, double y, int dir)
{
	Melee::meleeAttack(x, y, dir);
	_angle = (_dir == 1) ? _iniAngle - 40 :  _iniAngle + 40;
}

void Sword::update(double deltaTime)
{
	if (isActive())
	{
		_angle += _speed * _dir;
		double x, y;
		x = _center.getX() + _r * cos(_angle * M_PI / 180);
		y = _center.getY() + _r * sin(_angle * M_PI / 180);
		_body->getBody()->SetTransform(b2Vec2(x / M_TO_PIXEL, y / M_TO_PIXEL), 0);
	}
}