#pragma once
#include <string>
#include <vector>
#include "Vector2D.h"

using namespace std;
class ObjectLayer
{
private:
	std::vector<pair<Vector2D,string>> _objectsPos;
	std::string _name, _data = "";

public:
	ObjectLayer(std::string filename, std::string name);

	inline std::vector<pair<Vector2D, string>> getObjectsData() const { return _objectsPos; }
	inline std::string getName() { return _name; }
};