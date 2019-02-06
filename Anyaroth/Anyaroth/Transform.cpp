#include "Transform.h"



Transform::Transform() {
	position = Vector2D(0, 0);
	scale = Vector2D(1, 1);
	rotation = 0, 0;
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

double Transform::getRotation() {
	return rotation;
}

void Transform::setPosition(double x, double y) {
	position = Vector2D(x, y);
}

void Transform::setScale(double x, double y) {
	scale = Vector2D(x, y);
}

void Transform::setRotation(double rot) {
	rotation = rot;
}
