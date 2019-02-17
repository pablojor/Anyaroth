#include "TransformComponent.h"
#include "GameComponent.h"
#include "BodyComponent.h"

TransformComponent::TransformComponent(GameComponent* obj) 
{
	auto body = obj->getComponent<BodyComponent>();
	if (body != nullptr)
		_position = Vector2D((double)body->getBody()->GetPosition().x, (double)body->getBody()->GetPosition().y);
	else
		_position = Vector2D();
	_anchor = Vector2D();
	_scale = Vector2D(1, 1);
	_rotation = 0.0;
}