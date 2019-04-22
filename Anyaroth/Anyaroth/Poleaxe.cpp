#include "Poleaxe.h"
#include "Game.h"


Poleaxe::Poleaxe(Game * g, Vector2D offset, Uint16 collidesWith, double damage, double w, double h, GameObject* owner) : Melee(g, offset, collidesWith, damage, w, h, Poleaxe_Weapon)
{
	_owner = owner->getComponent<BodyComponent>();
}

Poleaxe::~Poleaxe()
{
}

void Poleaxe::update(const double & deltaTime)
{
	if (isActive())
	{
		_center = { _owner->getBody()->GetPosition().x * M_TO_PIXEL,_owner->getBody()->GetPosition().y * M_TO_PIXEL };
		_pos = { _body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL };
		_nextPos = _pos + _velocity * _dir;
		if (_nextPos.distance(_center) > _offset.getX())
		{
			_dir = -_dir;
			_nextPos = _pos + _velocity * _dir;
		}
		_pos = _nextPos;
		_body->getBody()->SetTransform(b2Vec2(_pos.getX() / M_TO_PIXEL, _pos.getY() / M_TO_PIXEL), 0);
	}
}
