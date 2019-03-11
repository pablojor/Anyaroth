#include "MeleeBox.h"
#include "Enemy.h"
#include "Game.h"
#include <math.h>

MeleeBox::MeleeBox(Game* g, double x, double y, double w, double h, double damage, Vector2D center, int dir,int type) : _damage(damage), _center(center), _type(type), _dir(dir), GameComponent(g, "Melee")
{
	_body = new BodyComponent(this, x, y, h, w);
	_body->filterCollisions(MELEE, ENEMIES);
	_body->getBody()->SetGravityScale(0);
	addComponent<BodyComponent>(_body);
	_pos = Vector2D(x, y);
	_size = Vector2D(w, h);
	_r = _pos.getY() - _center.getY();
}

void MeleeBox::update()
{
	_angle += 10 * _dir;
	switch (_type)
	{
	case(Knife):
	case(Chainsaw):
		break;
	case(Lightsaber):
	case(Axe):
		double x, y;
		x = _center.getX() + _r*cos(_angle *M_PI / 180);
		y = _center.getY() + _r*sin(_angle * M_PI / 180);
		_body->getBody()->SetTransform(b2Vec2(x/M_TO_PIXEL, y/M_TO_PIXEL), 0);
		break;
	}
}

void MeleeBox::beginCollision(GameComponent * other, b2Contact * contact)
{
	if (other->getTag() == "Enemy")
	{
		static_cast<Enemy*>(other)->subLife(_damage);
	}
}


MeleeBox::~MeleeBox()
{

}
