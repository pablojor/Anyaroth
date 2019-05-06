#include "BossPoleAxe.h"
#include "Game.h"


BossPoleAxe::BossPoleAxe(Game* game, GameObject* owner) : PoleAxe(game)
{
	_owner = owner->getComponent<BodyComponent>();
	_id = BossPoleAxe_Weapon;
}

BossPoleAxe::~BossPoleAxe()
{
}

void BossPoleAxe::update(const double & deltaTime)
{
	if (isActive())
	{
		_center = { _owner->getBody()->GetPosition().x * M_TO_PIXEL,_owner->getBody()->GetPosition().y * M_TO_PIXEL };
		PoleAxe::update(deltaTime);
	}
}
