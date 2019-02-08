#include "Layer.h"
#include "Game.h"
#include "AnyarothError.h"

#include <sstream>

Layer::Layer(string name, Texture* t, string filename) :type(type), tileset(t)
{ 
	tilemap.clear();
	fstream file;
	file.open(filename);
	if (file.is_open())
	{
		int temp = 0, h=0, w=0;
		bool found = false, cont = true;
		string n = "", data;
		//lee el archivo hasta que encuentra la layer que se quiere
		while ((!found || cont)  && n!="}")
		{
			getline(file, n, ':');
			//guardamos los datos en caso de que sea la capa que queremos
			if (n == "         \"height\"")
			{
				getline(file, n);
				h = stoi(n);
			}
			else if (n == "         \"width\"")
			{
				getline(file, n);
				w = stoi(n);
				//como el width esta escrito despues del nombre solo cuando se ha encontrado y leido width se sale del bucle
				if (found)
					cont = false;
			}

			else 
			{
				getline(file, n);
				if (n[0] == '[')
					data = n;
				else if (n == '\"' + name + "\",")
					found = true;
			}
		}
		//convertimos los datos en input stream
		istringstream iss(data);
		//si no es el final del .json
		if (n!="}") {
			getline(iss, n, '[');
			for (int y = 0; y < h; y++)
			{
				for (int x = 0; x < w; x++)
				{
					getline(iss, n, ',');
					temp = stoi(n);
					temp--;
					Tile* tile = new Tile(x*TILES_W, y*TILES_H, (temp / t->getNumCols()), temp % t->getNumCols(), tileset);
					tilemap.push_back(tile);
				}
			}
		}
		else
			throw AnyarothError("El formato del tileset no es correcto");
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


void Layer::addInputComponent(InputComponent* ic) {
	for (Tile* t : tilemap)
	{
		t->addInputComponent(ic);
	}
}

void Layer::addPhysicsComponent(PhysicsComponent* pc) {
	for (Tile* t : tilemap)
	{
		t->addPhysicsComponent(pc);
	}
}

void Layer::addRenderComponent(RenderComponent* rc) {
	for (Tile* t : tilemap)
	{
		t->addRenderComponent(rc);
	}
}

void Layer::delInputComponent(InputComponent* ic) {
	for (Tile* t : tilemap)
	{
		t->delInputComponent(ic);
	}
}

void Layer::delPhysicsComponent(PhysicsComponent* pc) {
	for (Tile* t : tilemap)
	{
		t->delPhysicsComponent(pc);
	}
}

void Layer::delRenderComponent(RenderComponent* rc) {
	for (Tile* t : tilemap)
	{
		t->delRenderComponent(rc);
	}
}