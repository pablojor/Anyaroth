#include "Laser.h"
#include "Game.h"

Laser::Laser(Game* g, Vector2D pos, Texture* texture, Player* player, double damage) : GameObject(g, "Laser"), _damage(damage), _pos(pos), _player(player)
{
	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();
	_transform->setAnchor(-0.5, -0.01);
	_transform->setPosition(pos.getX(), pos.getY());

	_anim = addComponent<AnimatedSpriteComponent>();
	_anim->addAnim(AnimatedSpriteComponent::LaserShooting, 1, true);
	_anim->addAnim(AnimatedSpriteComponent::LaserWarning, 1, true);

	setActive(false);
}

void Laser::update(double deltaTime)
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

void Laser::Shoot()
{
	_anim->playAnim(AnimatedSpriteComponent::LaserShooting);
	b2Vec2 _pos = b2Vec2(_transform->getPosition().getX() / M_TO_PIXEL, _transform->getPosition().getY() / M_TO_PIXEL);

	if (_body == nullptr)
	{
		_body = addComponent<BodyComponent>();

		_body->filterCollisions(LASER, PLAYER);
		_body->getBody()->SetType(b2_kinematicBody);

		_body->getBody()->GetFixtureList()->SetSensor(true);

		_body->getBody()->SetTransform(_pos, _angle*M_PI / 180);
	}
	else
	{
		_body->getBody()->SetActive(true);
		_body->getBody()->SetTransform(_pos, _angle * M_PI / 180);
	}
}

void Laser::PreShoot(double angle)
{
	_anim->playAnim(AnimatedSpriteComponent::LaserWarning); 
	setActive(true); 

	_transform->setRotation(angle);
	_angle = angle;
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