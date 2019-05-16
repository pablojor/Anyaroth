#include "PoleAxe.h"
#include "Game.h"

PoleAxe::PoleAxe(Game * game) : Melee(game, { 0, 0 }, ENEMIES, 15, 60, 30, PoleAxe_Weapon)
{
}

PoleAxe::~PoleAxe() {}

void PoleAxe::update(double deltaTime)
{
	if (isActive())
	{
		_pos = { _body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL };
		_nextPos = _pos + _velocity * (double)_dir;
		if (_nextPos.distance(_center) > _offset.getX())
		{
			_dir = -_dir;
			_nextPos = _pos + _velocity * (double)_dir;
		}
		_pos = _nextPos;
		_body->getBody()->SetTransform(b2Vec2(_pos.getX() / M_TO_PIXEL, _pos.getY() / M_TO_PIXEL), 0);
	}
}