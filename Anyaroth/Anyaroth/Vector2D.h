#pragma once

class Vector2D
{
private:
	double _x;
	double _y;

public:
	Vector2D();
	Vector2D(double x, double y) : _x(x), _y(y) {}

	double getX() const;
	double getY() const;

	void normalize();

	Vector2D operator+(const Vector2D& v) const;
	Vector2D operator-(const Vector2D& v) const;
	Vector2D operator*(double d) const;
	Vector2D operator*(float d) const;
	double operator*(const Vector2D& d) const;

	Vector2D rotate(double degrees);
	Vector2D rotateAroundPoint(double angle, Vector2D center);
	double distance(Vector2D p);

	static Vector2D Lerp(const Vector2D& start, const Vector2D& end, float t);
};