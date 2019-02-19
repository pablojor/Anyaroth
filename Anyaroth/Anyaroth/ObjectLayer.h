#pragma once
#include "GameComponent.h"

template<typename Object>
class ObjectLayer :	public GameComponent
{
public:
	ObjectLayer(string name, Texture* t, string filename, Game* g) : GameComponent(g)
	{
		fstream file;
		file.open(filename);
		if (file.is_open())
		{
			int temp = 0;
			bool found = false;
			string n = "", data;
			//lee el archivo hasta que encuentra la layer que se quiere
			while (!found && n != "}")
			{
				getline(file, n, ':');
				getline(file, n, ',');
				if (n == '\"' + name + "\"")
					found = true;

			}
			//convertimos los datos en input stream
			//si no es el final del .json
			while (n != "}],")
			{
				getline(file, n, '{');
				while (n != "}")
				{
					getline(file, n, ':');
					if (n == "\n         \"height\"")
					{
						getline(file, n, ',');
						temp = stoi(n);
						h = temp;
					}
					else if (n == "\n         \"width\"")
					{
						getline(file, n, ',');
						temp = stoi(n);
						w = temp;
					}
					else if (n == "\n         \"x\"")
					{
						getline(file, n, ',');
						temp = stoi(n);
						x = temp;
					}
					else if (n == "\n         \"y\"")
					{
						getline(file, n, ',');
						temp = stoi(n);
						y = temp;
					}
					else
						getline(file, n, ',');
				}
				new Object(t, g);
			}
		}
		else
			throw AnyarothError("El formato del tileset no es correcto");
		file.close();
	}
	virtual ~ObjectLayer() {};

	private:
		double x, y, h, w;
};

