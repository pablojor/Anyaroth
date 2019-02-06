#pragma once
#include "Vector2D.h"

class TransformComponent {
private:
	Vector2D position;
	Vector2D scale;
	double rotation;
public:
	TransformComponent();
	~TransformComponent();
	void activate() {}

	Vector2D getPosition();
	Vector2D getScale();
	double getRotation();

	void setPosition(double x, double y);
	void setScale(double x, double y);
	void setRotation(double rot);
};

