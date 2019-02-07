#include "TransformComponent.h"

Vector2D TransformComponent::getPosition() 
{
	return _position;
}

Vector2D TransformComponent::getScale() 
{
	return _scale;
}

Vector2D TransformComponent::getAnchor()
{
	return _anchor;
}

double TransformComponent::getRotation() 
{
	return _rotation;
}

//-------------------------

void TransformComponent::setPosition(double x, double y) 
{
	_position = Vector2D(x, y);
}

void TransformComponent::setScale(double x, double y) 
{
	_scale = Vector2D(x, y);
}

void TransformComponent::setScale(double a) 
{
	_scale = Vector2D(a, a);
}

void TransformComponent::setAnchor(double x, double y)
{
	_anchor = Vector2D(x, y);
}

void TransformComponent::setAnchor(double a)
{
	_anchor = Vector2D(a, a);
}

void TransformComponent::setRotation(double rot) 
{
	_rotation = rot;
}
