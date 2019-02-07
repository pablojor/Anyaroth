#include "TransformComponent.h"

Vector2D TransformComponent::getPosition() 
{
	return position;
}

Vector2D TransformComponent::getSize()
{
	return size;
}

Vector2D TransformComponent::getScale() 
{
	return scale;
}

Vector2D TransformComponent::getAnchor()
{
	return anchor;
}

double TransformComponent::getRotation() 
{
	return rotation;
}

//-------------------------

void TransformComponent::setPosition(double x, double y) 
{
	position = Vector2D(x, y);
}

void TransformComponent::setScale(double x, double y) 
{
	scale = Vector2D(x, y);
}

void TransformComponent::setScale(double a) 
{
	scale = Vector2D(a, a);
}

void TransformComponent::setAnchor(double x, double y)
{
	anchor = Vector2D(x, y);
}

void TransformComponent::setAnchor(double a)
{
	anchor = Vector2D(a, a);
}

void TransformComponent::setRotation(double rot) 
{
	rotation = rot;
}
