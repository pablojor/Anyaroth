#include "Tilemap.h"
#include "Game.h"
#include "Camera.h"
#include <json.hpp>

using namespace nlohmann;

Tilemap::Tilemap(Game* game, Texture* tileSet) : GameObject(game)
{
	_tileSet = tileSet;
	_tileSize = _tileSet->getW() / _tileSet->getNumCols();
}

Tilemap::~Tilemap()
{
	for (b2Body* b : _colliders)
		getWorld()->DestroyBody(b);

	_colliders.clear();
}

void Tilemap::render(Camera * c) const
{
	auto camPos = c->getCameraPosition();
	auto camSize = c->getCameraSize();

	int pXIndex = camPos.getX() / _tileSize + 1;
	int pYIndex = camPos.getY() / _tileSize + 1;
	int colsInCam = camSize.getX() / _tileSize + 1; if (colsInCam > _maxCols) colsInCam = _maxCols;
	int filsInCam = camSize.getY() / _tileSize + 1; if (filsInCam > _maxFils) filsInCam = _maxFils;

	int pIndex = pXIndex + (pYIndex - 1) * _maxCols;

	//Por cada fila que quepa en camara
	while (filsInCam >= 0)
	{
		//Por cada una de las columnas llevas de tiles
		auto beginOfFil = _grid.upper_bound(pIndex - 1);
		auto endOfFil = _grid.lower_bound(pIndex + colsInCam + 1);

		if (beginOfFil != _grid.end() && (*beginOfFil).first <= pIndex + colsInCam)
		{
			while (beginOfFil != endOfFil)
			{
				//Fila y columna de la textura
				auto aux = (*beginOfFil).second;
				std::vector<Tile> casilla = aux.getTiles();
				for (int i = 0; i < casilla.size(); i++)
				{
					Tile t = casilla[i];;
					int row = (t.tilesetIndex - 1) / _tileSet->getNumCols();
					int col = (t.tilesetIndex - 1) % _tileSet->getNumCols();

					SDL_Rect destRect = { t.xIndex * _tileSize - c->getCameraPosition().getX(), t.yIndex * _tileSize - c->getCameraPosition().getY(), _tileSize, _tileSize };

					SDL_Rect winRect = { destRect.x * GAME_RESOLUTION_X / c->getCameraSize().getX(), destRect.y * GAME_RESOLUTION_Y / c->getCameraSize().getY(),
						destRect.w * GAME_RESOLUTION_X / c->getCameraSize().getX() + 1, destRect.h * GAME_RESOLUTION_Y / c->getCameraSize().getY() + 1 }; //+1 para el tema del Zoom

					_tileSet->renderFrame(winRect, row, col);
				}		
				beginOfFil++;		
			}
		}

		filsInCam--;
		pIndex += _maxCols;
	}
}

void Tilemap::loadTileMap(const string & filename)
{
	json data;
	fstream file;
	file.open(filename);

	if (file.is_open())
	{
		file >> data;
		data = data["layers"];
		
		int index, height = 0, width = 0;
		string type, name;

		for (int i = 0; i < data.size(); i++)
		{
			json layer = data[i];

			auto it = layer.find("type");
			if (it != layer.end())
				type = (*it).get<string>();

			if (type == "tilelayer")
			{
				it = layer.find("name");
				if (it != layer.end())
					name = (*it).get<string>();

				it = layer.find("height");
				if (it != layer.end())
					height = *it;

				it = layer.find("width");
				if (it != layer.end())
					width = *it;

				it = layer.find("data");
				if (it != layer.end())
					layer = *it;

				int indexCount = 1;
				_maxFils = height;
				_maxCols = width;

				for (int i = 0; i < _maxFils * _maxCols; i++)
				{
					if (layer[i] != 0)
					{
						int y = i / _maxCols;
						int x = i % _maxCols;

						_grid[i + 1].getTiles().push_back(Tile(layer[i], x, y));

						if ((name == "Ground" || name == "Platform" || name == "Door" || name == "Death") && !_grid[i + 1].hasCollider())
						{
							_grid[i + 1].setTag(name);

							b2BodyDef bodydef;
							bodydef.type = b2_staticBody;
							bodydef.position = b2Vec2(x*_tileSize / M_TO_PIXEL + 1, y*_tileSize / M_TO_PIXEL + 1);
							bodydef.angle = 0.0;
							b2Body* body = getWorld()->CreateBody(&bodydef);

							b2PolygonShape shape;
							shape.SetAsBox(_tileSize / (M_TO_PIXEL * 2), _tileSize / (M_TO_PIXEL * 2));

							b2FixtureDef fixture;
							fixture.shape = &shape;
							fixture.density = 1;
							fixture.restitution = 0;
							fixture.friction = 0.001;
							if (name == "Death")
								fixture.isSensor = true;

							body->CreateFixture(&fixture);
							body->SetUserData(&_grid[i + 1]);
							body->SetFixedRotation(true);

							_colliders.push_back(body);
							_grid[i + 1].setHasCollider(true);
						}
					}
				}
			}
		}

		file.close();
	}
	else
		throw AnyarothError("No se ha encontrado el archivo introducido");
}