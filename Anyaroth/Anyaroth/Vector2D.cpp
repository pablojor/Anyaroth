#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D() : x(), y() {}

double Vector2D::getX() const 
{
	return x;
}

double Vector2D::getY() const 
{
	return y;
}

void Vector2D::normalize() 
{
	double mag = sqrt(pow(x, 2) + pow(y, 2));
	if (mag > 0.0) 
	{
		x = x / mag;
		y = y / mag;
	}
}

Vector2D Vector2D::operator+(const Vector2D& v) const 
{
	Vector2D r;
	r.x = this->x + v.x; // El this no es necesario. Se pone para ilustrar su uso
	r.y = this->y + v.y; // Al ser un puntero se debe usar con ->
	return r;
}

Vector2D Vector2D::operator-(const Vector2D& v) const
{
	Vector2D r;
	r.x = this->x - v.x; // El this no es necesario. Se pone para ilustrar su uso
	r.y = this->y - v.y; // Al ser un puntero se debe usar con ->
	return r;
}

Vector2D Vector2D::operator*(double d) const 
{
	Vector2D r;
	r.x = x * d;
	r.y = y * d;
	return r;
}

double Vector2D::operator*(const Vector2D& d) const 
{
	return d.x * x + d.y * y;
}
