#include "TransformComponent.h"
#include "GameComponent.h"


TransformComponent::TransformComponent(GameComponent* obj) 
{
	_anchor = Vector2D(0, 0);
	_position = Vector2D(0, 0);
	_scale = Vector2D(1, 1);
	_rotation = 0.0;
}