#include "MeleeComponent.h"
#include "IAControllerComponent.h"
#include "GameComponent.h"

MeleeComponent::MeleeComponent(GameComponent* obj) : PhysicsComponent(obj)
{
	_ia = obj->getComponent<IAControllerComponent>();
	if (_ia == nullptr)
		_ia = obj->addComponent<IAControllerComponent>();

	_anim = obj->getComponent<AnimatedSpriteComponent>();
	if (_anim == nullptr)
		_anim = obj->addComponent<AnimatedSpriteComponent>();
}

void MeleeComponent::attack()
{
	_time = SDL_GetTicks();
	_attacking = true;
}

void MeleeComponent::stop()
{
	_ia->noLongerAttacking();
	_attacking = false;
}

void MeleeComponent::update()
{
	if (_attacking)
	{
		if (SDL_GetTicks() > _time + 1000)
		{
			stop();
		}
	}
}