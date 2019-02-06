#include "TransformComponent.h"



TransformComponent::TransformComponent() {
	position = Vector2D(0, 0);
	scale = Vector2D(1, 1);
	rotation = 0, 0;
}


TransformComponent::~TransformComponent()
{
}

Vector2D TransformComponent::getPosition() {
	return position;
}

Vector2D TransformComponent::getScale() {
	return scale;
}

double TransformComponent::getRotation() {
	return rotation;
}

void TransformComponent::setPosition(double x, double y) {
	position = Vector2D(x, y);
}

void TransformComponent::setScale(double x, double y) {
	scale = Vector2D(x, y);
}

void TransformComponent::setRotation(double rot) {
	rotation = rot;
}
