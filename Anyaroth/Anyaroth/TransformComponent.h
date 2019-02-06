#pragma once
#include "Vector2D.h"

class TransformComponent {
private:
	Vector2D anchor;
	Vector2D position;
	Vector2D scale;
	double rotation;
public:
	TransformComponent();
	~TransformComponent();
	void activate() {}

	Vector2D getAnchor();
	Vector2D getPosition();
	Vector2D getScale();
	double getRotation();

	void setAnchor(double x, double y);
	void setAnchor(double a);
	void setPosition(double x, double y);
	void setScale(double x, double y);
	void setScale(double a);
	void setRotation(double rot);
};

