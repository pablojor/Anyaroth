#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D() : _x(), _y() {}

double Vector2D::getX() const 
{
	return _x;
}

double Vector2D::getY() const 
{
	return _y;
}

void Vector2D::normalize() 
{
	double mag = sqrt(pow(_x, 2) + pow(_y, 2));
	if (mag > 0.0) 
	{
		_x = _x / mag;
		_y = _y / mag;
	}
}

Vector2D Vector2D::operator+(const Vector2D& v) const 
{
	Vector2D r;
	r._x = this->_x + v._x; // El this no es necesario. Se pone para ilustrar su uso
	r._y = this->_y + v._y; // Al ser un puntero se debe usar con ->
	return r;
}

Vector2D Vector2D::operator-(const Vector2D& v) const
{
	Vector2D r;
	r._x = this->_x - v._x; // El this no es necesario. Se pone para ilustrar su uso
	r._y = this->_y - v._y; // Al ser un puntero se debe usar con ->
	return r;
}

Vector2D Vector2D::operator*(double d) const 
{
	Vector2D r;
	r._x = _x * d;
	r._y = _y * d;
	return r;
}

double Vector2D::operator*(const Vector2D& d) const 
{
	return d._x * _x + d._y * _y;
}