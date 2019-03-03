#include "HurtRenderComponent.h"
#include "Texture.h"
#include "GameComponent.h"

HurtRenderComponent::HurtRenderComponent(GameComponent * obj) : PhysicsComponent(obj)
{
	_texture = obj->getComponent<Texture>();
}


HurtRenderComponent::~HurtRenderComponent()
{
}

void HurtRenderComponent::update()
{
	if (_hurt && SDL_GetTicks() > _startTime)
	{
		_texture->setColor(255, 255, 255); //color original
		_hurt = false;
		
	}
}

void HurtRenderComponent::hurt()
{
	_texture->setColor(255, 0, 0);
	_startTime = SDL_GetTicks() + _hurtTime;
	_hurt = true;
}

void HurtRenderComponent::die()
{
	_texture->setColor(180, 180, 180);
}
