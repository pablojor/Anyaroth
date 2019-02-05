#include "Layer.h"
#include "Game.h"

Layer::Layer() 
{
	Surf_Tileset = nullptr;
}

Layer::~Layer() 
{ 
	tilemap.clear();
}

bool Layer::LoadTilemap(string filename)
{
	tilemap.clear();

	fstream file;
	file.open(filename);
	if (!file.is_open())
	{
		return false;
	}
	else
	{
		int temp = 0;
		file >> type;
		for (int x = 0; x < TILES_X; x++)
		{
			for (int y = 0; y < TILES_Y; y++)
			{
				file >> temp;
				tilemap.push_back(new Tile(temp, x*TILES_W, y*TILES_H));
			}
		}
		file.close();

		return true;
	}
}