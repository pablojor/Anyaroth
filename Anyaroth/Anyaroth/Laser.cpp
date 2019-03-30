#include "Laser.h"
#include "Game.h"

Laser::Laser(Game* g, Vector2D pos, Texture* texture, double w, double h, double damage) : GameObject(g, "Laser"), _damage(damage), _w(w), _h(h), _pos(pos)
{
	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(pos.getX(), pos.getY());

	_anim = addComponent<SpriteComponent>();
}


void Laser::Shoot(int angle)
{
	_angle = angle;

	_transform->setRotation(angle);
	if (_body == nullptr)
	{
		addComponent<BodyComponent>();

		_body->filterCollisions(LASER, PLAYER);
		_body->getBody()->SetType(b2_kinematicBody);
		_body->getBody()->GetFixtureList()->SetSensor(true);
	}
}