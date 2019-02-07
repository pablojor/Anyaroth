#pragma once
#include "Vector2D.h"

class TransformComponent 
{
	private:
		Vector2D _position = Vector2D(0, 0);
		Vector2D _scale = Vector2D(1, 1);
		Vector2D _anchor = Vector2D(0, 0);

		double _rotation = 0;

	public:
		TransformComponent() {}
		TransformComponent(Vector2D position, Vector2D scale = Vector2D(1, 1), Vector2D anchor = Vector2D(0, 0), double rotation = 0) :
			_position(position), _scale(scale), _anchor(anchor), _rotation(rotation) {}
		~TransformComponent() {}

		Vector2D getAnchor();
		Vector2D getPosition();
		Vector2D getScale();
		double getRotation();

		void setPosition(double x, double y);
		void setScale(double x, double y);
		void setScale(double a); void setAnchor(double x, double y);
		void setAnchor(double a);
		void setRotation(double rot);
};

