#include "Transform.h"



Transform::Transform(GameComponent* _parent) : Component(_parent) {
	position = Vector2D(0, 0);
	scale = Vector2D(1, 1);
	rotation = Vector2D(0, 0);
}


Transform::~Transform()
{
}

Vector2D Transform::getPosition() {
	return position;
}

Vector2D Transform::getScale() {
	return scale;
}

Vector2D Transform::getRotation() {
	return rotation;
}

void Transform::setPosition(double x, double y) {
	position = Vector2D(x, y);
}

void Transform::setScale(double x, double y) {
	scale = Vector2D(x, y);
}

void Transform::setRotation(double x, double y) {
	rotation = Vector2D(x, y);
}
