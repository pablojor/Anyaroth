#include "Laser.h"
#include "Game.h"

Laser::Laser(Game* g, Vector2D pos, Texture* texture, Player* player, double damage) : GameObject(g, "Laser"), _damage(damage), _pos(pos), _player(player)
{
	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(pos.getX(), pos.getY());

	_anim = addComponent<SpriteComponent>();

	setActive(false);
}
void Laser::update(const double& deltaTime)
{
	if (isActive())
	{
		if (colliding)
		{
			if (startedDamaging >= timeToDmg)
			{
				_player->subLife(_damage);
				startedDamaging = 0;
			}
			else
				startedDamaging += deltaTime;
		}
	}
}

void Laser::Shoot(double angle)
{
	setActive(true);

	_angle = angle;
	_transform->setRotation(angle);

	if (_body == nullptr)
	{
		_body = addComponent<BodyComponent>();

		_body->filterCollisions(LASER, PLAYER);
		_body->getBody()->SetType(b2_kinematicBody);
		//Provisional
		_body->setH(400);
		_body->setW(3);

		_body->getBody()->GetFixtureList()->SetSensor(true);

		_body->getBody()->SetTransform(_body->getBody()->GetPosition(), (_angle-90) * M_PI/180);
	}
	else
	{
		_body->getBody()->SetActive(true);
		_body->getBody()->SetTransform(_body->getBody()->GetPosition(), (_angle-90) * M_PI / 180);
	}
}

void Laser::Stop()
{
	setActive(false);

	_body->getBody()->SetActive(false);
	
}

void Laser::beginCollision(GameObject* other, b2Contact* contact)
{
	if (other->getTag() == "Player")
	{
		colliding = true;
	}
}

void Laser::endCollision(GameObject* other, b2Contact* contact)
{
	if (other->getTag() == "Player")
	{
		colliding = false;
		startedDamaging = 301;
	}
}