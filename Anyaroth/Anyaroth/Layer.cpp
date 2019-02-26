#include "Layer.h"
#include "Game.h"
#include "AnyarothError.h"
#include <json.hpp>

using namespace nlohmann;

Layer::Layer(string name, Texture* t, string filename, Game* g) : GameComponent(g), _tileset(t)
{
	json j;
	_tilemap.clear();
	fstream file;
	file.open(filename);
	if (file.is_open())
	{
		file >> j;
		j = j["layers"];
		int i = 0;
		bool cont = true;
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

		if (i != j.size())
		{
			int index, h = 0, w = 0;
			j = j[i];

			auto it = j.find("height");
			if (it != j.end())
				h = *it;

			it = j.find("width");
			if (it != j.end())
				w = *it;

			it = j.find("data");
			if (it != j.end())
				j = *it;
			int temp;
			for (int y = 0; y < h; y++)
			{
				for (int x = 0; x < w; x++)
				{
					temp = j[(y*w) + (x)];
					temp--;
					if (temp >= 0)
					{
						Tile* tile = new Tile(x * TILES_W, y * TILES_H, (temp / t->getNumCols()), temp % t->getNumCols(), _tileset, g);
						_tilemap.push_back(tile);
					}
				}
			}
		}
		else
			throw AnyarothError("No se ha encontrado la capa introducida");
		file.close();
	}
	else throw AnyarothError("No se ha encontrado el archivo");
}

Layer::~Layer()
{
	for (Tile* t : _tilemap)
	{
		delete t;
	}
}


void Layer::render() const
{
	for (Tile* t : _tilemap)
	{
		t->render();
	}
}