#pragma once
#include <string>
#include <vector>
#include "Vector2D.h"

class ObjectLayer
{
private:
	std::vector<Vector2D> _objectsPos;
	std::string _name;

public:
	ObjectLayer(std::string filename, std::string name);

	inline std::vector<Vector2D> getObjectsPositions() const { return _objectsPos; }
	inline std::string getName() { return _name; }
};