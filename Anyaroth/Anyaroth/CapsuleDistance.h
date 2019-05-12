#pragma once
#include "Capsule.h"

template<typename Spawned>
class CapsuleDistance :	public Capsule
{
private:
	BulletPool* _pool = nullptr;
public:
	CapsuleDistance(Game* g, Player* player, Vector2D pos, Enemy* father, BulletPool* pool) : Capsule(g, player, pos, father), _pool(pool) {};
	void spawn();
	virtual ~CapsuleDistance() {};
};


template<typename Spawned>
void CapsuleDistance<Spawned>::spawn()
{
	if (_spawning)
	{
		Vector2D pos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL - TILES_SIZE * 2, _body->getBody()->GetPosition().y * M_TO_PIXEL - TILES_SIZE * 2);
		_father->addChild(new Spawned(_game, _player, pos, _pool));
		_spawning = false;
		destroy();
	}
}
