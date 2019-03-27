#include "HurtRenderComponent.h"
#include "Texture.h"
#include "GameComponent.h"

HurtRenderComponent::HurtRenderComponent(GameComponent * obj) : PhysicsComponent(obj)
{
	_texture = obj->getComponent<Texture>();
}

void HurtRenderComponent::update(const double& deltaTime)
{
	_timer += deltaTime;

	if (_hurt && _timer >= _startTime)
	{
		_texture->setColor(255, 255, 255); //color original
		_hurt = false;
		_timer = 0;
	}
}

void HurtRenderComponent::hurt()
{
	_texture->setColor(255, 0, 0);
	_startTime = _timer + _hurtTime;
	_hurt = true;
}

void HurtRenderComponent::die()
{
	_texture->setColor(180, 180, 180);
}