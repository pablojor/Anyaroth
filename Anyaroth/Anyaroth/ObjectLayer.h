#pragma once
#include "GameComponent.h"

template<typename Object, typename Parameter1>
class ObjectLayer :	public GameComponent
{
public:
	ObjectLayer(string name, Texture* t, string filename, Game* g, Parameter1 p = Parameter1()) : GameComponent(g)
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
			bool cont = true;

			while (n != "                }],")
			{
				getline(file, n, '{');
				while (cont)
				{
					getline(file, n, ':');
					if (n == "                 \"height\"")
					{
						getline(file, n, ',');
						temp = stoi(n);
						h = temp;
					}
					else if (n == "                 \"width\"")
					{
						getline(file, n, ',');
						temp = stoi(n);
						w = temp;
					}
					else if (n == "                 \"x\"")
					{
						getline(file, n, ',');
						temp = stoi(n);
						x = temp;
					}
					else if (n == "                 \"y\"")
					{
						getline(file, n);
						temp = stoi(n);
						y = temp;
						cont = false;
					}
					else
						getline(file, n, ',');
					getline(file, n);
				}
				
				_objects.push_back(new Object(g, t, Vector2D(x, y), p));

				cont = true;
			}
		}
		else
			throw AnyarothError("No se ha encontrado la capa de objetos");
		file.close();
	}
	virtual ~ObjectLayer() { for (int i = 0; i < _objects.size(); i++) _objects.pop_back(); };

	int getNumObjects() { return _objects.size(); };
	Object* getObject(int i) { return _objects.at(i); };
	vector<Object*> getObjects() { return _objects; };

	private:
		double x, y, h, w;
		vector<Object*> _objects;
		
};

