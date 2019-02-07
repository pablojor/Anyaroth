#include "Layer.h"
#include "Game.h"

Layer::Layer(int type, Texture* t, string filename) :type(type), tileset(t)
{ 
	tilemap.clear();
	fstream file;
	file.open(filename);
	if (file.is_open())
	{
		int temp = 0;
		string n = "";
		getline(file, n);
		//lee el archivo hasta que encuentra la layer del tipo que se quiere
		while (n != "type: " + to_string(type) || !file.end)
		{
			getline(file, n);
		}

		//lineas del .json que no nos importan
		getline(file, n, '[');
		for (int x = 0; x < TILES_X; x++)
		{
			for (int y = 0; y < TILES_Y; y++)
			{
				getline(file, n, ',');
				temp = stoi(n);
				Tile* tile = new Tile(x*TILES_W, y*TILES_H, temp % TILES_X, (temp / TILES_X), tileset);
				//if (type == 1)
					//tile->addPhysicsComponent();

				tilemap.push_back(tile);
			}
		}
		file.close();

	}
}

Layer::~Layer() 
{ 
	tilemap.clear();
}


void Layer::render(Uint32 time)
{
	for (Tile* t : tilemap)
	{
		t->render(time);
	}
}