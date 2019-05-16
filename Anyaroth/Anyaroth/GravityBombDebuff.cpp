#include "GravityBombDebuff.h"
#include "BodyComponent.h"
#include "Game.h"

GravityBombDebuff::GravityBombDebuff(GameObject* obj, GameObject* gravityZone) : _obj(obj), _gravityZone(gravityZone), PhysicsComponent(obj)
{
	obj->addComponent(this);
	_active = true;
}

GravityBombDebuff::~GravityBombDebuff()
{
}

void GravityBombDebuff::changeDir()
{
	_dir = { ((_gravityZone->getComponent<TransformComponent>()->getPosition().getX()) - (_obj->getComponent<TransformComponent>()->getPosition().getX() - _obj->getComponent<BodyComponent>()->getW() / 2) - 25)*M_TO_PIXEL,
		((_gravityZone->getComponent<TransformComponent>()->getPosition().getY() - _gravityZone->getComponent<BodyComponent>()->getH() / 2) - (_obj->getComponent<TransformComponent>()->getPosition().getY() - _obj->getComponent<BodyComponent>()->getH() / 2))*M_TO_PIXEL };

	_dir.normalize();
}

void GravityBombDebuff::absorb()
{
	_obj->setStunned(true);
	_active = true;

	changeDir();
}

void GravityBombDebuff::stop() 
{
	if (_obj != nullptr)
	{
		_active = false;
		//_obj->setStunned(false);
	}
}

void GravityBombDebuff::update(double deltaTime)
{
	if (_active && _obj->isActive())
	{
		double dist = _obj->getComponent<TransformComponent>()->getPosition().distance(_gravityZone->getComponent<TransformComponent>()->getPosition());

		if (dist > _minDistance)
		{
			changeDir();

			if (_obj->isAffectedByExternalForces())
			{
				auto body = _obj->getComponent<BodyComponent>();
				body->getBody()->SetLinearVelocity(b2Vec2(_dir.getX() * _absorbSpeed, _dir.getY() * _absorbSpeed));
			}	
		}

		_damageTime += deltaTime;

		if (_damageTime >= _damageTickTime)
		{
			_obj->subLife(_gravityZone->getDamage());
			_damageTime = 0;
		}
	}
}