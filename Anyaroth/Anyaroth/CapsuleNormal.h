#pragma once
#include "Capsule.h"

template<typename Spawned>
class CapsuleNormal : public Capsule
{
public:
	CapsuleNormal(Game* g, Player* player, Vector2D pos, Enemy* father) : Capsule(g, player, pos, father) {};
	void spawn();
	virtual ~CapsuleNormal() {};
};
template<typename Spawned>
void CapsuleNormal<Spawned>::spawn()
{
	if (_spawning)
	{
		Vector2D pos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL - TILES_SIZE * 2, _body->getBody()->GetPosition().y * M_TO_PIXEL - TILES_SIZE * 2);
		_father->addChild(new Spawned(_game, _player, pos));
		_spawning = false;
		destroy();
	}
}