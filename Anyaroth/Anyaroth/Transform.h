#pragma once
#include "Vector2D.h"

class Transform {
private:
	Vector2D position;
	Vector2D scale;
	double rotation;
public:
	Transform();
	~Transform();
	void activate() {}

	Vector2D getPosition();
	Vector2D getScale();
	double getRotation();

	void setPosition(double x, double y);
	void setScale(double x, double y);
	void setRotation(double rot);
};

