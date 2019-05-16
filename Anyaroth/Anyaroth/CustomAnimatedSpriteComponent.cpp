#include "CustomAnimatedSpriteComponent.h"


CustomAnimatedSpriteComponent::CustomAnimatedSpriteComponent(GameObject* obj) : AnimatedSpriteComponent(obj), RenderComponent(obj){}


void CustomAnimatedSpriteComponent::render(Camera * c) const
{
	if (state == Hurt)
		_texture->setColor(255, 0, 0);
	else if (state == Dead)
		_texture->setColor(180, 180, 180);

	AnimatedSpriteComponent::render(c);

	if(state != Default)
		_texture->setColor(255, 255, 255);
}

void CustomAnimatedSpriteComponent::update(double deltaTime)
{
	AnimatedSpriteComponent::update(deltaTime);
	if (state == Hurt) 
	{	
		_timer += deltaTime;
		if (_timer >= _hurtTime)
		{
			state = Default;
			_timer = 0;
		}
	}
}
