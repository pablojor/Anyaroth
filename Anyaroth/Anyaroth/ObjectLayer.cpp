#include "ObjectLayer.h"
#include <json.hpp>

using namespace nlohmann;

ObjectLayer::ObjectLayer(string filename, string name)
{
	{
		fstream file;
		file.open(filename);
		if (file.is_open())
		{
			json j;
			file >> j;
			j = j["layers"];
			int i = 0;
			bool cont = true, found = true;
			while (i < j.size() && cont)
			{
				auto it = j[i].find("name");
				if (it != j[i].end())
				{
					cont = *it != name;
					if (cont)
						i++;
				}
			}
			j = j[i];
			auto it = j.find("objects");
			if (it != j.end())
			{
				j = *it;
				double x = 0, y = 0;
				for (int i = 0; i < j.size(); i++)
				{
					it = j[i].find("x");
					if (it != j[i].end())
						x = *it;

					it = j[i].find("y");
					if (it != j[i].end())
						y = *it;

					_objectsPos.push_back(Vector2D(x, y));
				}
			}
			else
				throw AnyarothError("No se ha encontrado la capa introducida");

			file.close();
		}
		else
			throw AnyarothError("No se ha encontrado el archivo introducido");
	}
}