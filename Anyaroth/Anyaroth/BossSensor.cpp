#include "BossSensor.h"
#include "FollowingComponent.h"
#include "BodyComponent.h"
#include "TransformComponent.h"
#include "Boss3.h"


BossSensor::BossSensor(Game * g, Boss3 * owner, Vector2D size, Vector2D offset) : GameObject(g, "BossSensor"), _owner(owner), _offset(offset)
{
	Vector2D ownerPos = { _owner->getComponent<BodyComponent>()->getBody()->GetPosition().x * M_TO_PIXEL, _owner->getComponent<BodyComponent>()->getBody()->GetPosition().y * M_TO_PIXEL };
	TransformComponent* t = addComponent <TransformComponent>();
	t->setPosition(ownerPos.getX() + offset.getX(), ownerPos.getY() + offset.getY());

	BodyComponent* body = addComponent<BodyComponent>();
	body->setH(size.getX());
	body->setW(size.getY());
	body->filterCollisions(FLOOR, PLAYER_BULLETS);
	body->getBody()->GetFixtureList()->SetSensor(true);

	FollowingComponent* f = addComponent<FollowingComponent>(_owner);
	f->setInitialOffset(_offset);
}

void BossSensor::beginCollision(GameObject * other, b2Contact * contact)
{
	if (other->getTag() == "Bullet")
		_owner->setBulletApproaching(true);
}

BossSensor::~BossSensor()
{
}
