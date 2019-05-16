#include "BossPoleAxe.h"
#include "Game.h"

BossPoleAxe::BossPoleAxe(Game* game, GameObject* owner) : PoleAxe(game)
{
	_owner = owner->getComponent<BodyComponent>();
	setCollisionFilters(PLAYER);
	setCollisionSize({ 40, 75 });
	setOffset({ 115,15 });
	setDamage(7);
	setVelocity({ 18,0 });

	_id = BossPoleAxe_Weapon;
}

BossPoleAxe::~BossPoleAxe() {}

void BossPoleAxe::update(double deltaTime)
{
	if (isActive())
	{
		_center = { _owner->getBody()->GetPosition().x * M_TO_PIXEL,_owner->getBody()->GetPosition().y * M_TO_PIXEL };
		PoleAxe::update(deltaTime);
	}
}